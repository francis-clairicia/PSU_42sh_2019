/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** Adds nodes to argument list matching with wildcards.
*/

#include "mysh_parsing.h"

static void apply_wildcards_to_node(parse_list_t *cur_node,
                                    arguments_t **tmp)
{
    arguments_t *save_tmp = (*tmp)->next;

    if (add_args_for_matching(&cur_node->cmd_list->args, *tmp)) {
        remove_node_from_arg_list_index(&cur_node->cmd_list->args, *tmp);
        (*tmp) = save_tmp;
    }
}

static bool can_treat_wildcards(const parse_list_t *node)
{
    if (!node || !(node->cmd_list) || !node->cmd_list->prev->args)
        return (false);
    if (node->cmd_list->prev->prev->redir_output_type == PIPE)
        return (false);
    if (node->cmd_list->args->prev == node->cmd_list->args)
        return (false);
    return (true);
}

void apply_wildcards_changes(parse_list_t *cur_node)
{
    arguments_t *tmp = NULL;

    if (!can_treat_wildcards(cur_node))
        return;
    tmp = cur_node->cmd_list->prev->args->next;
    do {
        if (WILDCARDS_IN_STR(tmp->arg))
            apply_wildcards_to_node(cur_node, &tmp);
        tmp = tmp->next;
    } while (tmp != cur_node->cmd_list->prev->args);
}
