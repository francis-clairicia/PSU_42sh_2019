/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_find_var_env.c
*/

#include <criterion/criterion.h>
#include "minishell.h"

Test(find_var_env, find_out_a_variable_in_environment)
{
    char *envp[] = {"USER=a", "HOSTNAME=localhost", "PATH=", NULL};

    cr_expect_eq(find_var_env(envp, "USER"), 0);
    cr_expect_eq(find_var_env(envp, "PATH"), 2);
    cr_expect_eq(find_var_env(envp, "UNKNOWN"), -1);
}

Test(find_var_env, handle_null_value)
{
    char *envp[] = {"USER=a", "HOSTNAME=localhost", "PATH=", NULL};

    cr_expect_eq(find_var_env(NULL, "USER"), -1);
    cr_expect_eq(find_var_env(envp, NULL), -1);
}