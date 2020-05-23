/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** fg.c
*/

#include "minishell.h"

static int handle_status(node_t *node, shell_t *shell)
{
    int wstatus = 0;
    void (*destroy)(process_t *) = &destroy_process_struct;

    my_printf("%s\n", NODE_DATA(node, process_t *)->cmd);
    waitpid(NODE_DATA(node, process_t *)->pid, &wstatus, 0);
    if (WIFSIGNALED(wstatus)) {
        if (WTERMSIG(wstatus) != SIGINT) {
            print_signal(WTERMSIG(wstatus), WCOREDUMP(wstatus), true);
            my_delete_node(&shell->process, node, destroy);
            return (-1);
        }
        my_putstr_error("\n");
    }
    my_delete_node(&shell->process, node, destroy);
    return (set_exit_status(shell, (unsigned char)WEXITSTATUS(wstatus)));
}

static bool find_process(node_t **node, char const *job, shell_t *shell)
{
    process_t *process = NULL;

    if (job[0] != '%' && !my_str_isnum(job)) {
        print_error("fg", "No such job");
        return (set_exit_status(shell, 1));
    }
    for (*node = shell->process.start; *node; *node = (*node)->next) {
        process = NODE_DATA(*node, process_t *);
        if (job[0] != '%' && process->pid == my_getnbr(job))
            return (true);
        if (job[0] == '%' &&
        ((my_str_isnum(&job[1]) && process->pid == my_getnbr(&job[1])) ||
        (!my_str_isnum(&job[1]) &&
        my_strncmp(&job[1], process->cmd, my_strlen(&job[1])) == 0))) {
            return (true);
        }
    }
    print_error("fg", "No such job");
    return (set_exit_status(shell, 1));
}

int fg_builtin_command(char * const *av, shell_t *shell)
{
    node_t *node = NULL;
    int ac = my_array_len(av);

    if (ac == 1) {
        node = my_node(shell->process, 0);
        if (!node) {
            print_error("fg", "No current job");
            return (set_exit_status(shell, 1));
        }
        return (handle_status(node, shell));
    }
    set_exit_status(shell, 0);
    for (int i = 1; find_process(&node, av[i], shell); i += 1)
        handle_status(node, shell);
    return ((shell->exit_status == 0) ? 0 : -1);
}