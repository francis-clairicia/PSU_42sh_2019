/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** get_args_from_output.c
*/

#include "minishell.h"

static char **run_command(char const *command_line, int pipefd[2],
    int *pid, shell_t *shell)
{
    char *line = NULL;
    char *whole_buffer = NULL;
    char **array = NULL;

    *pid = fork();
    if (*pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        exit(eval_exec_cmd(command_line, shell));
    }
    close(pipefd[1]);
    while (get_next_line_2(&line, pipefd[0])) {
        whole_buffer = my_strcat_malloc(whole_buffer, line, true, false);
        whole_buffer = my_strcat_malloc(whole_buffer, "\n", true, false);
    }
    close(pipefd[0]);
    array = my_str_to_word_array(whole_buffer, " \t\n");
    free(whole_buffer);
    return (array);
}

static void set_arguments_to_list(arguments_t **args_list, char **args_array)
{
    for (int i = 0; args_array[i]; i += 1) {
        add_arg_list_node(args_list);
        if (!(*args_list))
            break;
        (*args_list)->prev->arg = args_array[i];
    }
    free(args_array);
}

void get_args_from_output(arguments_t **args, char const *command_line,
    shell_t *shell)
{
    int pipefd[2] = {0, 0};
    char **array_args = NULL;
    int child_pid = 0;
    int wstatus = 0;

    if (!args || !command_line)
        return;
    if (pipe(pipefd) == -1)
        return;
    array_args = run_command(command_line, pipefd, &child_pid, shell);
    waitpid(child_pid, &wstatus, 0);
    if (array_args && WIFEXITED(wstatus) && WEXITSTATUS(wstatus) != 1)
        set_arguments_to_list(args, array_args);
    else
        my_free_array(array_args);
}