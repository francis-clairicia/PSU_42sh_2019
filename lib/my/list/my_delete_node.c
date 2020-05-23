/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_delete_node.c
*/

#include "mylist.h"

void my_delete_node(list_t *list, node_t *node, void (*free_function)())
{
    if (!my_remove_node(list, node))
        return;
    if (free_function != NULL && NODE_DATA(node, void *) != NULL)
        free_function(NODE_DATA(node, void *));
    free(node->data.ptr);
    free(node);
}