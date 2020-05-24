/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** check_process.c
*/

#include "minishell.h"

static void print_process_status(process_t *process)
{
    int wstatus = 0;

    if (process->running) {
        if (__getpgid(process->pid) < 0)
            process->running = false;
        return;
    }
    waitpid(process->pid, &wstatus, 0);
    my_printf("[%lu]\t", process->index);
    if (WEXITSTATUS(wstatus) == 0)
        my_putstr("Done");
    else if (WEXITSTATUS(wstatus) > 127)
        print_signal(WEXITSTATUS(wstatus) - 127, false, false);
    else
        my_printf("Exit %d", WEXITSTATUS(wstatus));
    my_printf("\t%s\n", process->cmd);
    process->checked = true;
}

static void check_process_status(list_t *process_list, node_t **node,
    list_t *node_to_delete)
{
    node_t *actual = *node;
    process_t *process = NODE_DATA(actual, process_t *);

    *node = (*node)->next;
    if (process->checked) {
        my_remove_node(process_list, actual);
        my_insert_node(node_to_delete, actual, -1, 0);
    }
}

void check_background_process(shell_t *shell)
{
    node_t *node = NULL;
    list_t node_to_delete = my_list();

    if (!shell)
        return;
    for (node = shell->process.start; node; node = node->next)
        print_process_status(NODE_DATA(node, process_t *));
    node = shell->process.start;
    while (node)
        check_process_status(&shell->process, &node, &node_to_delete);
    my_free_list(&node_to_delete, &destroy_process_struct);
}