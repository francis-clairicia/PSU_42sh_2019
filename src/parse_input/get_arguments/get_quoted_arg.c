/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** Gets a quoted argument.
*/

#include "my.h"
#include "mysh_parsing.h"

void get_quoted_arg(cmd_list_t **head, const bool separator,
                        const char *input, size_t *i)
{
    const char backstick = input[*i];
    char **last_arg = NULL;
    char *tmp = NULL;

    *i += 1;
    tmp = my_strdup_char_i(&(input[*i]), backstick, i);
    if (!separator && (*head)->prev->args) {
        last_arg = &((*head)->prev->args->prev->arg);
        *last_arg = my_strcat_malloc(*last_arg, tmp, true, true);
    } else {
        add_arg_list_node(&(*head)->prev->args);
        (*head)->prev->args->prev->arg = tmp;
    }
    *i += 1;
}