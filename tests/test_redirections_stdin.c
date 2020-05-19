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

Test(stdin_redirection, read_a_file_as_standard_input)
{
    char **envp = my_array_dup(DEFAULT_ENVIRONMENT);
    int fd = open("tests/file_1.txt", O_CREAT | O_WRONLY, 0664);

    cr_redirect_stdout();
    my_putstr_fd(fd, "Yoo\n");
    close(fd);
    cr_expect_eq(minishell("cat -e < tests/file_1.txt", &envp), 0);
    my_free_array(envp);
    remove("tests/file_1.txt");
    cr_expect_stdout_eq_str("Yoo$\n");
}

static void print_on_fd_for_stdin_test(int fd)
{
    my_putstr_fd(fd, "Bonjour\n");
    my_putstr_fd(fd, "C'est moi\n");
    my_putstr_fd(fd, "Sans EOF\n");
    my_putstr_fd(fd, "EOF\n");
}

Test(stdin_redirection, handle_here_document_redirection)
{
    char **envp = my_array_dup(DEFAULT_ENVIRONMENT);
    int pipefd[2];
    int child = 0;

    cr_assert_eq(pipe(pipefd), 0);
    child = fork();
    if (child == 0) {
        close(pipefd[0]);
        print_on_fd_for_stdin_test(pipefd[1]);
        close(pipefd[1]);
        exit(0);
    }
    close(pipefd[1]);
    dup2(pipefd[0], 0);
    waitpid(child, NULL, 0);
    cr_redirect_stdout();
    cr_expect_eq(minishell("cat << EOF", &envp), 0);
    my_free_array(envp);
    cr_expect_stdout_eq_str("? ? ? ? " "Bonjour\nC'est moi\nSans EOF\n");
    close(pipefd[0]);
}

Test(stdin_redirection, print_error_if_there_is_no_file)
{
    char **envp = my_array_dup(DEFAULT_ENVIRONMENT);

    cr_redirect_stderr();
    cr_expect_eq(minishell("cat < ", &envp), -1);
    my_free_array(envp);
    cr_expect_stderr_eq_str("Missing name for redirect.\n");
}

Test(stdin_redirection, print_error_if_can_t_open_file)
{
    char **envp = my_array_dup(DEFAULT_ENVIRONMENT);

    cr_redirect_stderr();
    cr_expect_eq(minishell("cat < unknown_file.unknown", &envp), -1);
    my_free_array(envp);
    cr_expect_stderr_eq_str("unknown_file.unknown: "
        "No such file or directory.\n");
}