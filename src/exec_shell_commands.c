/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** exec_shell_commands.c
*/

#include <string.h>
#include "minishell.h"

static int handle_status(int child_pid, int status_pipe)
{
    int wstatus = 0;

    waitpid(child_pid, &wstatus, 0);
    if (WIFSIGNALED(wstatus)) {
        if (WTERMSIG(wstatus) != SIGINT) {
            print_signal(WTERMSIG(wstatus), WCOREDUMP(wstatus));
            return (-1);
        }
        my_putstr_error("\n");
    }
    return (status_pipe);
}

static int launch_process(char const *binary, command_t commands[],
    char ***envp)
{
    int status_pipe = 0;
    int child_pid = 0;
    command_t *command = &commands[0];

    if (binary == NULL || command->input_fd == -1 || command->output_fd == -1)
        return (-1);
    child_pid = fork();
    if (child_pid == 0) {
        dup2(command->input_fd, STDIN_FILENO);
        dup2(command->output_fd, STDOUT_FILENO);
        dup2(command->error_fd, STDERR_FILENO);
        if (execve(binary, command->argv, *envp) < 0)
            print_error(command->argv[0], error_exec(errno));
        return (1);
    }
    destroy_command(command);
    if (commands[1].argv != NULL)
        status_pipe = exec_shell_commands(&commands[1], envp);
    return (handle_status(child_pid, status_pipe));
}

int exec_shell_commands(command_t commands[], char ***envp)
{
    char *path_to_executable = NULL;
    int status = 0;
    builtin_t builtin = NULL;
    command_t *command = NULL;

    if (commands == NULL || commands[0].argv == NULL)
        return (-1);
    bind_sigint_signal(PROCESS);
    command = &commands[0];
    builtin = is_builtin(command->argv);
    if (builtin != NULL) {
        status = launch_builtin(builtin, commands, envp);
    } else {
        path_to_executable = get_path_to_executable(command->argv[0], *envp);
        status = launch_process(path_to_executable, commands, envp);
        free(path_to_executable);
    }
    return (status);
}