/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** check_process.c
*/

#include "minishell.h"

static void print_process(char const *cmd)
{
    if (!cmd)
        return;
    my_printf("\t%s", cmd);
}

static void print_process_status(process_t *process)
{
    int wstatus = 0;

    waitpid(process->pid, &wstatus, 0);
    if (WIFEXITED(wstatus)) {
        if (WEXITSTATUS(wstatus) == 0)
            my_putstr("Done");
        else
            my_printf("Exit %d", WEXITSTATUS(wstatus));
    }
    if (WIFSIGNALED(wstatus))
        print_signal(WTERMSIG(wstatus), false, false);
    print_process(process->cmd);
    if (WIFSIGNALED(wstatus) && WCOREDUMP(wstatus))
        my_putstr(" (core dumped)");
    my_putchar('\n');
}

static void check_process_status(node_t *node, list_t *node_to_delete)
{
    process_t *process = NODE_DATA_PTR(node, process_t);

    if (__getpgid(process->pid) >= 0)
        return;
    my_printf("[%lu]\t", node->index);
    print_process_status(process);
    my_put_in_list(node_to_delete, node->index, size_t);
}

void check_background_process(shell_t *shell)
{
    list_t node_to_delete = my_list();

    if (!shell)
        return;
    for (node_t *node = shell->process.start; node; node = node->next) {
        check_process_status(node, &node_to_delete);
    }
    for (node_t *node = node_to_delete.start; node; node = node->next) {
        my_delete_node(&(shell->process), NODE_DATA(node, size_t), NULL);
    }
    my_free_list(&node_to_delete, NULL);
}