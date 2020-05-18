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
        GET_ELEM_END(node, size, 16) = (size_t)node;
        GET_ELEM_END(node, size, 8) = (size_t)node;
        *head = node;
    } else {
        GET_ELEM_END(node, size, 16) = (size_t)(*head);
        GET_ELEM_END(node, size, 8) = GET_ELEM_END(head, size, 8);
        GET_ELEM_END(GET_ELEM_END(*head, size, 8), size, 16) = (size_t)node;
        GET_ELEM_END(*head, size, 8) = (size_t)node;
    }
    return (node);
}