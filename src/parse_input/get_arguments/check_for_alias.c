/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** check_for_alias.c
*/

#include <stdlib.h>
#include "mysh_parsing.h"

static void apply_alias(arguments_t **head, char **alias_array)
{
    register size_t index = 0;

    if (!alias_array)
        return;
    if (!remove_node_from_arg_list_index(head, (*head)))
        return;
    (*head) = NULL;
    for (; alias_array[index]; index += 1) {
        add_arg_list_node(head);
        (*head)->prev->arg = my_strdup(alias_array[index]);
    }
}

void check_for_alias(shell_t *shell, cmd_list_t **cmd,
                    cmd_list_t **last_cmd)
{
    alias_t *tmp = NULL;

    if (!shell || !(shell->alias_list) || !cmd ||!(*cmd) || !(*cmd)->args)
        return;
    if (!(*last_cmd))
        *last_cmd = (*cmd);
    else if (*last_cmd == (*cmd))
        return;
    if (!(*last_cmd))
        return;
    for (tmp = shell->alias_list; tmp; tmp = tmp->next) {
        if (!my_strcmp((*cmd)->args->arg, tmp->alias)) {
            apply_alias(&(*cmd)->args, tmp->cmd);
        }
    }
    *last_cmd = (*cmd);
}