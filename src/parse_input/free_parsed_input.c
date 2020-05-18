/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Frees the parsed input nodes and lists.
*/

#include <stdlib.h>
#include "mysh_parsing.h"

void free_argument(arguments_t *node)
{
    if (!node)
        return;
    if (node->arg) {
        free(node->arg);
    }
}

void free_cmd(cmd_list_t *node)
{
    if (!node)
        return;
    if (node->args) {
        DCLL_FREE_NODE_LIST(node->args);
    }
    if (node->redir_name) {
        free(node->redir_name);
    }
}

void free_parsed_input(parsed_input_list_t *node)
{
    if (!node)
        return;
    if (node->cmd_list) {
        DCLL_FREE_NODE_LIST(node->cmd_list);
    }
}