/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** minishell.c
*/

#include "minishell.h"

static bool exec_next_command(parse_list_t **node,
    parse_list_t *list, int index, int status)
{
    if (index == 0)
        return (true);
    if (status == 1)
        return (false);
    if ((*node)->splitter == AND) {
        if (status < 0) {
            return (false);
        }
    } else if ((*node)->splitter == OR) {
        if (status == 0) {
            return (false);
        }
    }
    (*node) = (*node)->next;
    if (*node == list)
        return (false);
    return (true);
}

static int exec_command(cmd_list_t *cmd_list, shell_t *shell, bool background)
{
    process_t *process = NULL;
    int child_pid = 0;

    if (!background)
        return (exec_piped_commands(cmd_list, shell));
    child_pid = fork();
    if (child_pid == 0) {
        exec_piped_commands(cmd_list, shell);
        exit(shell->exit_status);
    }
    process = init_process_struct(child_pid, cmd_list);
    if (process) {
        my_append_to_list(&(shell->process), process, process_t *);
        process->index = shell->process.size;
        my_printf("[%lu] %d\n", process->index, process->pid);
    }
    return (0);
}

static int launch_all_commands(parse_list_t *list, shell_t *shell)
{
    int i = 0;
    int status = 0;
    int error = 0;
    parse_list_t *node = list;

    while (exec_next_command(&node, list, i, status)) {
        status = exec_command(node->cmd_list, shell, (node->splitter == BG));
        if (status < 0)
            error = 1;
        i += 1;
    }
    return ((!error || status == 1) ? status : -1);
}

int eval_exec_cmd(char const *command_line, shell_t *shell)
{
    parse_error_t error = NONE;
    parse_list_t *list = NULL;
    int status = 0;

    list = parse_input(shell, command_line, &error);
    if (error != NONE || (!shell)) {
        print_parsing_error(error);
        status = -1;
    } else {
        status = launch_all_commands(list, shell);
    }
    free_parse_list(list);
    return (status);
}
