/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Gets a quoted argument.
*/

#include "my.h"
#include "parsing.h"

void get_quoted_arg(cmd_list_t **head, const bool separator,
                        const char *input, size_t *i)
{
    const char inhib = input[*i];
    char *tmp = NULL;

    *i += 1;
    tmp = my_strdup_char_i(&(input[*i]), inhib, i);
    if (!separator && (*head)->prev->args)
        (*head)->prev->args->prev->arg = my_strcat((*head)->prev->args->prev->arg, tmp, 1, 1);
    else {
        add_node_to_arg_list(&(*head)->prev->args);
        (*head)->prev->args->prev->arg = tmp;
    }
    *i += 1;
}