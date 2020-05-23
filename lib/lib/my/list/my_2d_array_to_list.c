/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** my_2d_array_to_list.c
*/

#include "mylist.h"

list_t my_2d_array_to_list(void *array)
{
    list_t list = my_list();

    for (int i = 0; ((void **)array)[i] != NULL; i += 1) {
        my_append_to_list(&list, ((void **)array)[i], void *);
    }
    return (list);
}