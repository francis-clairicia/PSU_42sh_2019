/*
** EPITECH PROJECT, 2019
** 42sh
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
    if (!separator && ((cmd_list_t *)DCLL_PREV((*head)))->args) {
        last_arg = &((arguments_t *)DCLL_PREV(((cmd_list_t *)DCLL_PREV(*head))->args))->arg;
        last_arg = &((*head)->prev->args->prev->arg);
        *last_arg = my_strcat(*last_arg, tmp, true, true);
    } else {
        DCLL_ADD_NODE(&((cmd_list_t *)DCLL_PREV((*head)))->args,
                                sizeof(arguments_t), free_cmd);
        (*head)->prev->args->prev->arg = tmp;
    }
    *i += 1;
}