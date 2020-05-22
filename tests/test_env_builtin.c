/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_env_builtin.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(env_builtin_command, print_environment)
{
    char *custom_env[] = {"YO=2", NULL};
    shell_t *shell = init_shell_struct(custom_env);

    cr_redirect_stdout();
    cr_expect_eq(eval_exec_cmd("env", shell), 0);
    cr_expect_stdout_eq_str("YO=2\n");
    destroy_shell_struct(shell);
}

Test(env_builtin_command, handle_args)
{
    cr_redirect_stderr();
    cr_expect_eq(eval_exec_cmd("env -i", NULL), -1);
    cr_expect_stderr_eq_str("env: Too many arguments.\n");
}

Test(env_builtin_command, handle_null_env)
{
    shell_t *shell = init_shell_struct(NULL);

    cr_redirect_stdout();
    cr_expect_eq(eval_exec_cmd("env", shell), -1);
    destroy_shell_struct(shell);
}