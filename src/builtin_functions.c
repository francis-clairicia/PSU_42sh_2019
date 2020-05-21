/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** builtin_functions.c
*/

#include "minishell.h"

static const struct builtin builtin_functions_list[] = {
    {"cd", cd_builtin_command},
    {"env", env_builtin_command},
    {"exit", exit_builtin_command},
    {"setenv", setenv_builtin_command},
    {"unsetenv", unsetenv_builtin_command},
    {"alias", alias_builtin_command},
    {"unalias", unalias_builtin_command},
    {NULL, NULL}
};

builtin_t is_builtin(char * const *cmd)
{
    int i = 0;

    if (cmd == NULL)
        return (NULL);
    while (builtin_functions_list[i].command != NULL) {
        if (my_strcmp(cmd[0], builtin_functions_list[i].command) == 0)
            return (builtin_functions_list[i].function);
        i += 1;
    }
    return (NULL);
}

static int exec_builtin(builtin_t builtin, command_t *command,
    shell_t *shell, bool in_fork)
{
    int save_stdout = dup(STDOUT_FILENO);
    int save_stderr = dup(STDERR_FILENO);
    int status = 0;

    dup2(command->output_fd, STDOUT_FILENO);
    dup2(command->error_fd, STDERR_FILENO);
    status = builtin(command->argv, shell);
    dup2(save_stdout, STDOUT_FILENO);
    dup2(save_stderr, STDERR_FILENO);
    return ((in_fork) ? 1 : (status));
}

int launch_builtin(builtin_t builtin, command_t commands[], shell_t *shell)
{
    command_t *command = &commands[0];
    int status = 0;
    int status_pipe = 0;
    int child_pid = -1;

    if (commands[1].argv == NULL) {
        status = exec_builtin(builtin, command, shell, false);
    } else {
        child_pid = fork();
        if (child_pid == 0)
            return (exec_builtin(builtin, command, shell, true));
    }
    destroy_command(command);
    if (commands[1].argv != NULL)
        status_pipe = exec_shell_commands(&commands[1], shell);
    if (child_pid != -1)
        waitpid(child_pid, NULL, 0);
    return ((status_pipe != 0) ? status_pipe : status);
}