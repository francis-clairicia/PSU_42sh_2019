/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** test_redirections.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include "minishell.h"

Test(stdout_redirection, write_on_a_file_instead_of_terminal)
{
    char **envp = my_array_dup(DEFAULT_ENVIRONMENT);
    FILE *file = NULL;

    cr_expect_eq(minishell("echo BONJOUR > tests/file_2.txt", &envp), 0);
    my_free_array(envp);
    file = fopen("tests/file_2.txt", "r");
    cr_expect_file_contents_eq_str(file, "BONJOUR\n");
    fclose(file);
    remove("tests/file_2.txt");
}

Test(stdout_redirection, append_to_a_file)
{
    char **envp = my_array_dup(DEFAULT_ENVIRONMENT);
    FILE *file = NULL;

    cr_expect_eq(minishell("echo BONJOUR >> tests/file_3.txt", &envp), 0);
    cr_expect_eq(minishell("echo Au_Revoir >> tests/file_3.txt", &envp), 0);
    my_free_array(envp);
    file = fopen("tests/file_3.txt", "r");
    cr_expect_file_contents_eq_str(file, "BONJOUR\nAu_Revoir\n");
    fclose(file);
    remove("tests/file_3.txt");
}

Test(stdout_redirection, print_error_if_there_is_no_file)
{
    char **envp = my_array_dup(DEFAULT_ENVIRONMENT);

    cr_redirect_stderr();
    cr_expect_eq(minishell("echo > ", &envp), -1);
    my_free_array(envp);
    cr_expect_stderr_eq_str("Missing name for redirect.\n");
}