/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** exec_piped_commands.c
*/

#include "minishell.h"

static bool link_all_commands(command_t commands[], int nb_commands)
{
    int pipefd[2];
    int i = 0;

    for (i = 1; i < nb_commands; i += 1) {
        if (pipe(pipefd) != 0)
            return (false);
        commands[i - 1].output_fd = pipefd[1];
        commands[i].input_fd = pipefd[0];
    }
    return (true);
}

static void destroy_all_commands(command_t commands[], int nb_commands)
{
    int i = 0;

    if (!commands)
        return;
    for (i = 0; i < nb_commands; i += 1)
        destroy_command(&commands[i]);
    free(commands);
}

int exec_piped_commands(cmd_list_t *cmd_list, char ***envp)
{
    int nb_commands = 0;
    command_t *commands = parse_cmd_list(cmd_list, &nb_commands);
    int status = 0;

    if (status == 0 && !commands)
        status = -1;
    if (status == 0 && !link_all_commands(commands, nb_commands))
        status = -1;
    if (status == 0)
        status = exec_shell_commands(commands, envp);
    destroy_all_commands(commands, nb_commands);
    return (status);
}