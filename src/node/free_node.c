/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** free_node
*/

#include "node.h"

void free_node_list(node_t *node)
{
    node_t *final = NULL;
    node_t *tmp = NULL;

    if (!node)
        return;
    final = node;
    tmp = node;
    do {
        node = node->next;
        if (tmp && tmp->freer)
            tmp->freer(tmp);
        if (tmp)
            free(tmp);
        tmp = node;
    } while (tmp != final);
}