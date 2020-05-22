/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** Parses a command_t.
*/

#include "minishell.h"

static bool is_a_tty_fd(int fd)
{
    return (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO);
}

command_t init_command_struct(void)
{
    command_t cmd;

    my_memset(&cmd, 0, sizeof(cmd));
    cmd.input_fd = STDIN_FILENO;
    cmd.output_fd = STDOUT_FILENO;
    cmd.error_fd = STDERR_FILENO;
    cmd.argv = NULL;
    return (cmd);
}

void destroy_command(command_t *command)
{
    if (!command)
        return;
    if (!is_a_tty_fd(command->input_fd) && command->input_fd != -1) {
        close(command->input_fd);
        command->input_fd = STDIN_FILENO;
    }
    if (!is_a_tty_fd(command->output_fd) && command->output_fd != -1) {
        close(command->output_fd);
        command->output_fd = STDOUT_FILENO;
    }
    my_free_array(command->argv);
    command->argv = NULL;
}