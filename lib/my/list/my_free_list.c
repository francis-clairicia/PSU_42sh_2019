/*
** EPITECH PROJECT, 2019
** my_free_list
** File description:
** Free data in list
*/

#include "mylist.h"

void my_free_list(list_t *list, void (*free_function)())
{
    if (list == NULL)
        return;
    while (list->size > 0)
        my_delete_node(list, list->end, free_function);
}
