/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** test_minishell.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(minishell, launch_command_like_an_another_shell)
{
    int status = 0;
    char **envp = my_array_dup(DEFAULT_ENVIRONMENT);

    cr_redirect_stdout();
    status = minishell("ls src/main.c", &envp);
    if (status == 1) {
        cr_expect_eq(kill(getpid(), SIGCHLD), 0);
    } else {
        cr_expect_eq(status, 0, "Expected 0, got %d", status);
        cr_expect_stdout_eq_str("src/main.c\n");
    }
    my_free_array(envp);
}

Test(minishell, handle_null_command)
{
    cr_assert_eq(minishell(NULL, NULL), 1);
}