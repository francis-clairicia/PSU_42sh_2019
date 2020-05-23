/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_remove_node.c
*/

#include "mylist.h"

static void remove_first_node(list_t *list)
{
    int i = 0;
    node_t *node = NULL;

    if (list->size == 1) {
        list->start = NULL;
        list->end = NULL;
    } else {
        list->start = list->start->next;
        list->start->previous = NULL;
        for (node = list->start; node != NULL; node = node->next)
            node->index = i++;
    }
}

static void remove_middle_node(node_t *node)
{
    node_t *previous_node;
    node_t *next_node;
    int index = node->index;

    previous_node = node->previous;
    next_node = node->next;
    previous_node->next = next_node;
    next_node->previous = previous_node;
    for (node = next_node; node != NULL; node = node->next)
        node->index = index++;
}

static void remove_last_node(list_t *list)
{
    list->end = list->end->previous;
    list->end->next = NULL;
}

int my_remove_node(list_t *list, node_t *node)
{
    if (!list || !node || !my_find_node(*list, node))
        return (0);
    if (node == list->start)
        remove_first_node(list);
    else if (node == list->end)
        remove_last_node(list);
    else
        remove_middle_node(node);
    list->size -= 1;
    return (1);
}