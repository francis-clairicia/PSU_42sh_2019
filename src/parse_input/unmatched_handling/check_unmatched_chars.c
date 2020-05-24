/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** check_unmatched_chars.c
*/

#include <stdbool.h>
#include <stddef.h>
#include "mysh_parsing.h"

static void set_error_char_val(error_parse_t *error, const char c)
{
    switch (c) {
        case ('\''):
            (*error) = UNMATCHED_SINGLE;
            break;
        case ('"'):
            (*error) = UNMATCHED_DOUBLE;
            break;
        case ('`'):
            (*error) = UNMATCHED_MAGIC;
            break;
    }
}

static void shift_to_next_match(const char *cmd, error_parse_t *error,
                                const char c, size_t *index)
{
    set_error_char_val(error, c);
    *index += 1;
    while (cmd[*index]) {
        if (cmd[*index] == c) {
            (*error) = NONE;
            return;
        }
        *index += 1;
    }
}

static void compare_with_quotes(const char *cmd, const char *quotes,
                                    error_parse_t *error, size_t *index)
{
    size_t i = 0;

    for (; quotes[i] && *error == NONE; i += 1) {
        if (cmd[*index] == quotes[i])
            shift_to_next_match(cmd, error, quotes[i], index);
    }
}

bool check_unmatched_chars(const char *cmd, error_parse_t *error)
{
    const char quotes[] = "'\"`";
    size_t index = 0;

    if (!cmd)
        return (false);
    for (; cmd[index] && (*error) == NONE; index += 1) {
        compare_with_quotes(cmd, quotes, error, &index);
    }
    return ((*error) == NONE) ? true : false;
}