/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_list_dup.c
*/

#include "mylist.h"

list_t my_list_dup(list_t list)
{
    list_t new_list = my_list();

    for (node_t *node = list.start; node; node = node->next) {
        my_insert_node(&new_list, node, -1, 1);
    }
    return (new_list);
}