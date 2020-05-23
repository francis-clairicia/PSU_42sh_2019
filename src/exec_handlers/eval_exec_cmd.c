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
    (*node) = (*node)->next;
    if (*node == list)
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
    return (true);
}

static int exec_command(cmd_list_t *cmd_list, shell_t *shell)
{
    int child_pid = 0;

    if (1)
        return (exec_piped_commands(cmd_list, shell));
    child_pid = fork();
    if (child_pid == 0) {
        exec_piped_commands(cmd_list, shell);
        return (1);
    }
    my_append_to_list(&(shell->process),
        init_process_struct(child_pid, cmd_list), process_t *);
    my_printf("[%d] %d\n", shell->process.size, child_pid);
    return (0);
}

static int launch_all_commands(parse_list_t *list, shell_t *shell)
{
    int i = 0;
    int status = 0;
    int error = 0;
    parse_list_t *node = list;

    while (exec_next_command(&node, list, i, status)) {
        status = exec_command(node->cmd_list, shell);
        if (status < 0)
            error = 1;
        i += 1;
    }
    return ((!error || status == 1) ? status : -1);
}

int eval_exec_cmd(char const *command_line, shell_t *shell)
{
    error_parse_t error = NONE;
    parse_list_t *list = parse_input(command_line, &error);
    int status = 0;

    if (error != NONE) {
        print_parsing_error(error);
        status = (list == NULL) ? 1 : -1;
    } else {
        status = launch_all_commands(list, shell);
    }
    free_parse_list(list);
    return (status);
}
