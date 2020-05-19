/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** test_env_builtin.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(env_builtin_command, print_environment)
{
    char **envp = NULL;

    cr_redirect_stdout();
    minishell("setenv YO 2", &envp);
    cr_expect_eq(minishell("env", &envp), 0);
    cr_expect_stdout_eq_str("YO=2\n");
    my_free_array(envp);
}

Test(env_builtin_command, handle_args)
{
    cr_redirect_stderr();
    cr_expect_eq(minishell("env -i", NULL), -1);
    cr_expect_stderr_eq_str("env: Too many arguments.\n");
}

Test(env_builtin_command, handle_null_env)
{
    char **envp = NULL;

    cr_assert_eq(minishell("env", &envp), -1);
}