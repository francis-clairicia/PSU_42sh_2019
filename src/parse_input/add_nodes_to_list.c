/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Adds nodes to certain lists.
*/

#include <stdlib.h>
#include "parsing.h"

void *add_parsing_node(void **head, const size_t size)
{
    void *node = NULL;

    if (!head)
        return (NULL);
    node = malloc(size);
    if (!node)
        return (NULL);
    my_memset(node, 0, size);
    if (!(*head)) {
        (*(size_t *)node) = (size_t)node;
        (*(size_t *)(node + 8)) = (size_t)node;
        *head = node;
    } else {
        (*(size_t *)node) = (size_t)(*head);
        (*(size_t *)(node + 8)) = (*(size_t *)((*head + 8)));
        (*(size_t *)((*(size_t *)((*head) + 8)))) = (size_t)node;
        (*(size_t *)((*head) + 8)) = (size_t)node;
    }
    return (node);
}