/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_minishell.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(minishell, launch_command_like_an_another_shell)
{
    int status = 0;
    shell_t *shell = init_shell_struct(DEFAULT_ENVIRONMENT);

    cr_redirect_stdout();
    status = eval_exec_cmd("ls src/main.c", shell);
    cr_expect_eq(status, 0, "Expected 0, got %d", status);
    cr_expect_stdout_eq_str("src/main.c\n");
    destroy_shell_struct(shell);
}

Test(minishell, handle_null_command)
{
    cr_assert_eq(eval_exec_cmd(NULL, NULL), -1);
}