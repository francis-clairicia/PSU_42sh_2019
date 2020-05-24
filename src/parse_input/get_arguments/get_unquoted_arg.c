/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** Gets a normal argument that doesn't have quotes.
*/

#include "my.h"
#include "mysh_parsing.h"

void get_unquoted_arg(cmd_list_t **head, indicator_t *indic)
{
    char **last_arg = NULL;
    char *tmp = NULL;

    tmp = my_strdup_list_i(&(indic->input[indic->i]),
                        FIRST_CHAR_STOPPER, &indic->i);
    if (!indic->separator && (*head)->prev->args) {
        last_arg = &((*head)->prev->args->prev->arg);
        *last_arg = my_strcat_malloc(*last_arg, tmp, true, true);
    } else {
        add_arg_list_node(&(*head)->prev->args);
        (*head)->prev->args->prev->arg = tmp;
    }
    indic->last_quotation = WAS_UNQUOTED;
}