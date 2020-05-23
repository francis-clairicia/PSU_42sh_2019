/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** check_unmatched_backticks.c
*/

#include <stdbool.h>
#include <stddef.h>
#include "mysh_parsing.h"

static void shift_to_next_backtick(const char *cmd, error_parse_t *error,
                                const char c, size_t *index)
{
    (*error) = (c == '"') ? UNMATCHED_DOUBLE : UNMATCHED_SINGLE;
    *index += 1;
    while (cmd[*index]) {
        if (cmd[*index] == c) {
            (*error) = NONE;
            return;
        }
        *index += 1;
    }
}

bool check_unmatched_backticks(const char *cmd, error_parse_t *error)
{
    size_t index = 0;

    if (!cmd)
        return (false);
    for (; cmd[index] && (*error) == NONE; index += 1) {
        if (cmd[index] == '\'')
            shift_to_next_backtick(cmd, error, '\'', &index);
        else if (cmd[index] == '"')
            shift_to_next_backtick(cmd, error, '"', &index);
    }
    return ((*error) == NONE) ? true : false;
}