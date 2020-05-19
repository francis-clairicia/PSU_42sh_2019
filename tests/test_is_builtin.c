/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** test_is_builtin.c
*/

#include <criterion/criterion.h>
#include "minishell.h"

Test(is_builtin, check_whether_command_typed_is_a_builtin)
{
    cr_expect_eq(is_builtin((char *[]){"env"}), env_builtin_command);
    cr_expect_eq(is_builtin((char *[]){"setenv"}), setenv_builtin_command);
    cr_expect_eq(is_builtin((char *[]){"unsetenv"}), unsetenv_builtin_command);
    cr_expect_eq(is_builtin((char *[]){"cd"}), cd_builtin_command);
    cr_expect_eq(is_builtin((char *[]){"exit"}), exit_builtin_command);
    cr_expect_eq(is_builtin((char *[]){"ls"}), NULL);
    cr_expect_eq(is_builtin(NULL), NULL);
}