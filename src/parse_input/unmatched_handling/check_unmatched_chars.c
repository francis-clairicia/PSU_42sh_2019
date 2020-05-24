/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** check_unmatched_chars.c
*/

#include <stdbool.h>
#include <stddef.h>
#include "mysh_parsing.h"

static void set_error_char_val(parse_error_t *error, const char c)
{
    switch (c) {
        case ('\''):
            (*error) = UNMATCHED_SINGLE;
            break;
        case ('"'):
            (*error) = UNMATCHED_DOUBLE;
            break;
        case (MAGIC_QUOTE_CHAR):
            (*error) = UNMATCHED_MAGIC;
            break;
    }
}

static void shift_to_next_match(const char *cmd, parse_error_t *error,
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

static void compare_with_quotes(const char *cmd, const char *all_to_match_chars,
                                parse_error_t *error, size_t *index)
{
    size_t i = 0;

    for (; all_to_match_chars[i] && *error == NONE; i += 1) {
        if (cmd[*index] == all_to_match_chars[i])
            shift_to_next_match(cmd, error, all_to_match_chars[i], index);
    }
}

bool check_unmatched_chars(const char *cmd, parse_error_t *error)
{
    const char all_to_match_chars[] = "'\"`";
    size_t index = 0;

    if (!cmd)
        return (false);
    for (; cmd[index] && (*error) == NONE; index += 1) {
        compare_with_quotes(cmd, all_to_match_chars, error, &index);
    }
    return ((*error) == NONE) ? true : false;
}