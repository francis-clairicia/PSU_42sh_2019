/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** rotate_list.c
*/

#include "mylist.h"

void rotate_begin_list(list_t *list)
{
    node_t *begin = NULL;

    if (!list)
        return;
    begin = list->start;
    my_remove_node(list, begin);
    my_insert_node(list, begin, -1, 0);
}

void rotate_end_list(list_t *list)
{
    node_t *end = NULL;

    if (!list)
        return;
    end = list->end;
    my_remove_node(list, end);
    my_insert_node(list, end, 0, 0);
}