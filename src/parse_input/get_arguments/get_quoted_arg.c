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
    const char backtick = input[*i];
    char *tmp = NULL;

    *i += 1;
    tmp = my_strdup_char_i(&(input[*i]), backtick, i);
    if (!separator && (*head)->prev->args)
        (*head)->prev->args->prev->arg = my_strcat_malloc(
            (*head)->prev->args->prev->arg, tmp, 1, 1);
    else {
        ADD_PARSE_NODE(&(*head)->prev->args, arguments_t);
        (*head)->prev->args->prev->arg = tmp;
    }
    *i += 1;
}