/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** change_fd.c
*/

#include <fcntl.h>
#include "minishell.h"

static int here_document_command(char const *end)
{
    char *line = NULL;
    int pipefd[2];

    if (pipe(pipefd) != 0)
        return (-1);
    while (my_putstr("? ")
    && get_next_line_2(&line, 0) && my_strcmp(line, end) != 0) {
        my_putstr_fd(pipefd[1], line);
        my_putstr_fd(pipefd[1], "\n");
    }
    close(pipefd[1]);
    if (line != NULL)
        free(line);
    return (pipefd[0]);
}

static int open_file(char const *file, int flags, int mode)
{
    int fd = open(file, flags, mode);

    if (fd == -1)
        print_error(file, strerror(errno));
    return (fd);
}

int get_input_fd(char const *file, redirection_type_t type)
{
    if (type == READ_FROM_FILE_AS_INPUT)
        return (open_file(file, O_RDONLY, 0));
    if (type == READ_FROM_STDIN_AS_INPUT)
        return (here_document_command(file));
    return (STDIN_FILENO);
}

int get_output_fd(char const *file, redirection_type_t type)
{
    int flags = O_CREAT | O_WRONLY;

    if (type == APPEND_TO_FILE || type == REDIR_IN_FILE) {
        flags |= ((type == APPEND_TO_FILE) ? (O_APPEND) : (O_TRUNC));
        return (open_file(file, flags, 0644));
    }
    return (STDOUT_FILENO);
}