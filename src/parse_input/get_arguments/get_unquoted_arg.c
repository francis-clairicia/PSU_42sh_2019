/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Gets a normal argument that doesn't have quotes.
*/

#include "my.h"
#include "parsing.h"

void get_unquoted_arg(cmd_list_t **head, const bool separator,
                        const char *input, size_t *i)
{
    char *tmp = NULL;

    tmp = my_strdup_list_i(&(input[(*i)]), all_splitters, i);
    if (!separator && (*head)->prev->args)
        (*head)->prev->args->prev->arg = my_strcat((*head)->prev->args->prev->arg, tmp, 1, 1);
    else {
        ADD_PARSE_NODE(&(*head)->prev->args, arguments_t);
        (*head)->prev->args->prev->arg = tmp;
    }
}