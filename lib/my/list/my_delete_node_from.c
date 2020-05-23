/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_delete_node_from.c
*/

#include "mylist.h"

void delete_node_from_data(list_t *list, const void *data, size_t size,
    void (*free_func)())
{
    node_t *node = NULL;

    if (list == NULL)
        return;
    node = node_from_data(*list, data, size);
    if (node == NULL)
        return;
    my_delete_node(list, node, free_func);
}

void my_delete_node_from_index(list_t *list, int index, void (*free_func)())
{
    node_t *node = NULL;

    if (list == NULL)
        return;
    node = my_node(*list, index);
    if (node == NULL)
        return;
    my_delete_node(list, node, free_func);
}