/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** get_array_from_arg_list.c
*/

#include <stdlib.h>
#include "my.h"
#include "mysh_parsing.h"

static size_t get_arg_list_size(arguments_t *arg_list)
{
    arguments_t *tmp = NULL;
    size_t size = 0;

    if (!arg_list)
        return (0);
    tmp = arg_list;
    do {
        size += 1;
        tmp = tmp->next;
    } while (tmp != arg_list);
    return (size);
}

char **get_array_from_arg_list(arguments_t *arg_list)
{
    arguments_t *tmp = NULL;
    size_t size = get_arg_list_size(arg_list);
    char **array = NULL;
    size_t i = 0;

    if (size <= 0)
        return (NULL);
    array = malloc(sizeof(char *) * (size + 1));
    if (!array)
        return (NULL);
    tmp = arg_list;
    do {
        array[i] = my_strdup(tmp->arg);
        i += 1;
        tmp = tmp->next;
    } while (tmp != arg_list);
    array[i] = NULL;
    return (array);
}