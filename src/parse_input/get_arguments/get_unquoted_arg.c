/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Gets a normal argument that doesn't have quotes.
*/

#include "my.h"
#include "mysh_parsing.h"

void get_unquoted_arg(cmd_list_t **head, const bool separator,
                        const char *input, size_t *i)
{
    char **last_arg = NULL;
    char *tmp = NULL;

    tmp = my_strdup_list_i(&(input[(*i)]), all_splitters, i);
    if (!separator && (*head)->prev->args) {
        last_arg = &((*head)->prev->args->prev->arg);
        *last_arg = my_strcat(*last_arg, tmp, true, true);
    } else {
        add_arg_list_node(&(*head)->prev->args);
        (*head)->prev->args->prev->arg = tmp;
    }
}