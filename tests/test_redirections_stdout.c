/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_redirections.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include "minishell.h"

Test(stdout_redirection, write_on_a_file_instead_of_terminal)
{
    shell_t *shell = init_shell_struct(DEFAULT_ENVIRONMENT);
    FILE *file = NULL;

    cr_expect_eq(eval_exec_cmd("echo BONJOUR > tests/file_2.txt", shell), 0);
    destroy_shell_struct(shell);
    file = fopen("tests/file_2.txt", "r");
    cr_expect_file_contents_eq_str(file, "BONJOUR\n");
    fclose(file);
    remove("tests/file_2.txt");
}

Test(stdout_redirection, append_to_a_file)
{
    shell_t *shell = init_shell_struct(DEFAULT_ENVIRONMENT);
    FILE *file = NULL;

    cr_expect_eq(eval_exec_cmd("echo BONJOUR >> tests/file_3.txt", shell), 0);
    cr_expect_eq(eval_exec_cmd("echo Au_Revoir >> tests/file_3.txt", shell), 0);
    destroy_shell_struct(shell);
    file = fopen("tests/file_3.txt", "r");
    cr_expect_file_contents_eq_str(file, "BONJOUR\nAu_Revoir\n");
    fclose(file);
    remove("tests/file_3.txt");
}

Test(stdout_redirection, print_error_if_there_is_no_file)
{
    shell_t *shell = init_shell_struct(DEFAULT_ENVIRONMENT);

    cr_redirect_stderr();
    cr_expect_eq(eval_exec_cmd("echo > ", shell), -1);
    destroy_shell_struct(shell);
    cr_expect_stderr_eq_str("Missing name for redirect.\n");
}