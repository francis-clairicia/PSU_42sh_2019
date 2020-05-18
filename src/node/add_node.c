/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** add_node
*/

#include "node.h"

static void * add_first_node(node_t **head, node_t *new_node)
{
    if (!head || !new_node)
        return (NULL);
    new_node->next = new_node;
    new_node->prev = new_node;
    *head = new_node;
}

static void * add_new_node(node_t **head, node_t *new_node)
{
    if (!head || !new_node)
        return (NULL);
    new_node->next = (*head);
    new_node->prev = (*head)->prev;
    (*head)->prev->next = new_node;
    (*head)->prev = new_node;
    return (new_node);
}

void *add_node(node_t **head, const size_t size, bool (*freer)(void *))
{
    node_t *new_node = NULL;

    if (!head || size < sizeof(node_t))
        return (NULL);
    new_node = malloc(size);
    if (!new_node)
        return (NULL);
    my_memset(new_node, 0, size);
    new_node->freer = freer;
    if (!(*head)) {
        return (add_first_node(head, new_node));
    } else {
        return (add_new_node(head, new_node));
    }
}