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
    if (!separator && DCLL_PREV_C(*head, cmd_list_t *)->args) {
        last_arg = &DCLL_PREV_C(
                    DCLL_PREV_C(*head, cmd_list_t *)->args, arguments_t *)->arg;
        *last_arg = my_strcat(*last_arg, tmp, true, true);
    } else {
        DCLL_ADD(
        &DCLL_PREV_C(*head, cmd_list_t *)->args, sizeof(cmd_list_t), free_cmd);
        DCLL_PREV_C(
        DCLL_PREV_C(*head, cmd_list_t *)->args, arguments_t *)->arg = tmp;
    }
    *i += 1;
}