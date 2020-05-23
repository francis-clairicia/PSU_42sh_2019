/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** check_unmatched_backticks.c
*/

#include <stdbool.h>
#include <stddef.h>
#include "mysh_parsing.h"

static int shift_to_next_backtick(const char *cmd, const char c,
                                    size_t *index)
{
    int unmatched = (c == '"') ? UNMATCHED_DOUBLE : UNMATCHED_SINGLE;

    *index += 1;
    while (cmd[*index]) {
        if (cmd[*index] == c) {
            return (NONE);
        }
        *index += 1;
    }
    return (unmatched);
}

bool check_unmatched_backticks(const char *cmd, error_parse_t *error)
{
    size_t index = 0;
    int unmatched = NONE;

    if (!cmd)
        return (false);
    for (; cmd[index] && unmatched == NONE; index += 1) {
        if (cmd[index] == '\'')
            unmatched = shift_to_next_backtick(cmd, '\'', &index);
        else if (cmd[index] == '"')
            unmatched = shift_to_next_backtick(cmd, '"', &index);
    }
    if (unmatched == NONE)
        return (true);
    *error = UNMATCHED_BACKTICKS;
    my_printf("Unmatched '%c'.\n", (unmatched == UNMATCHED_SINGLE) ? '\'': '"');
    return (false);
}