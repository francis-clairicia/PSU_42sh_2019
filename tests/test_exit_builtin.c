/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** test_exit_builtin.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(exit_builtin_command, close_the_minishell)
{
    shell_t *shell = init_shell_struct(DEFAULT_ENVIRONMENT);

    cr_redirect_stdout();
    cr_expect_eq(minishell("exit", shell), 1);
    cr_expect_stdout_eq_str("exit\n");
    destroy_shell_struct(shell);
}