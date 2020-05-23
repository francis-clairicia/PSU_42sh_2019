/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_unsetenv_builtin.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(unsetenv_builtin_command, remove_var_form_environment)
{
    shell_t *shell = init_shell_struct(NULL);

    eval_exec_cmd("setenv YO 2", shell);
    eval_exec_cmd("setenv USER user", shell);
    eval_exec_cmd("setenv DISPLAY :0.0", shell);
    cr_expect_neq(find_var_env(shell->envp, "YO"), -1);
    cr_expect_neq(find_var_env(shell->envp, "USER"), -1);
    cr_expect_neq(find_var_env(shell->envp, "DISPLAY"), -1);
    cr_expect_eq(eval_exec_cmd("unsetenv YO USER DISPLAY", shell), 0);
    cr_expect_eq(find_var_env(shell->envp, "YO"), -1);
    cr_expect_eq(find_var_env(shell->envp, "USER"), -1);
    cr_expect_eq(find_var_env(shell->envp, "DISPLAY"), -1);
    cr_expect_eq(eval_exec_cmd("unsetenv UNKNOWN_VAR_IN_ENV", shell), 0);
    destroy_shell_struct(shell);
}

Test(unsetenv_builtin_command, print_error_when_no_arg_is_given)
{
    cr_redirect_stderr();
    cr_expect_eq(eval_exec_cmd("unsetenv", NULL), -1);
    cr_expect_stderr_eq_str("unsetenv: Too few arguments.\n");
}