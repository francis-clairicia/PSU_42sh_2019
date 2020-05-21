/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** test_pipe.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(pipe_redirection, redirect_output_of_process_to_an_another)
{
    shell_t *shell = init_shell_struct(DEFAULT_ENVIRONMENT);

    cr_redirect_stdout();
    cr_expect_eq(minishell("echo Hello | cat -e | wc -c", shell), 0);
    destroy_shell_struct(shell);
    cr_expect_stdout_eq_str("7\n");
}

Test(pipe_redirection, print_error_if_it_already_have_a_stdin_redirection)
{
    shell_t *shell = init_shell_struct(DEFAULT_ENVIRONMENT);

    cr_redirect_stderr();
    cr_expect_eq(minishell("echo Hello | cat < Makefile", shell), -1);
    destroy_shell_struct(shell);
    cr_expect_stderr_eq_str("Ambiguous input redirect.\n");
}

Test(pipe_redirection, print_error_if_it_already_have_a_stdout_redirection)
{
    shell_t *shell = init_shell_struct(DEFAULT_ENVIRONMENT);

    cr_redirect_stderr();
    cr_expect_eq(minishell("echo Hello > output | cat -e", shell), -1);
    destroy_shell_struct(shell);
    cr_expect_stderr_eq_str("Ambiguous output redirect.\n");
    remove("output");
}