/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** test_setenv_builtin.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(setenv_builtin_command, add_var_to_environment_and_can_modify_it)
{
    shell_t *shell = init_shell_struct((char *[]){"USER=", NULL});

    cr_expect_eq(minishell("setenv USER user", shell), 0);
    cr_expect_eq(minishell("setenv HOSTNAME localhost", shell), 0);
    cr_expect_eq(minishell("setenv VAR", shell), 0);
    cr_assert_not_null(shell->envp);
    cr_expect_str_eq(shell->envp[0], "USER=user");
    cr_expect_str_eq(shell->envp[1], "HOSTNAME=localhost");
    cr_expect_str_eq(shell->envp[2], "VAR=");
    cr_expect_eq(minishell("setenv USER name", shell), 0);
    cr_expect_str_eq(shell->envp[0], "USER=name");
    destroy_shell_struct(shell);
}

Test(setenv_builtin_command, print_error_if_not_start_with_letter)
{
    shell_t *shell = init_shell_struct(NULL);
    char err[] = "setenv: Variable name must begin with a letter.\n";

    cr_redirect_stderr();
    cr_expect_eq(minishell("setenv 2VAR user", shell), -1);
    cr_expect_stderr_eq_str(err);
    destroy_shell_struct(shell);
}

Test(setenv_builtin_command, print_error_if_var_is_non_alphanumeric_string)
{
    shell_t *shell = init_shell_struct(NULL);
    char err[] = "setenv: "
        "Variable name must contain alphanumeric characters.\n";

    cr_redirect_stderr();
    cr_expect_eq(minishell("setenv VAR5:2 user", shell), -1);
    cr_expect_stderr_eq_str(err);
    destroy_shell_struct(shell);
}

Test(setenv_builtin_command, print_environment_when_no_args_is_given)
{
    shell_t *shell = init_shell_struct((char *[]){"YO=2", NULL});

    cr_redirect_stdout();
    cr_expect_eq(minishell("setenv", shell), 0);
    cr_expect_stdout_eq_str("YO=2\n");
    destroy_shell_struct(shell);
}

Test(setenv_builtin_command, print_error_when_too_many_args_are_given)
{
    shell_t *shell = init_shell_struct(NULL);
    char err[] = "setenv: Too many arguments.\n";

    cr_redirect_stderr();
    cr_expect_eq(minishell("setenv VAR value1 value2", shell), -1);
    cr_expect_stderr_eq_str(err);
    destroy_shell_struct(shell);
}