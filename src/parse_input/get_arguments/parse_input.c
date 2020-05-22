/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Parses the given input into a doubly circular linked list.
*/

#include <stdbool.h>
#include <stdlib.h>
#include "my.h"
#include "mysh_parsing.h"

static bool parse_each_argument(parse_list_t **head,
                                error_parse_t *error,
                                const char *input, size_t *i)
{
    parse_list_t **cur = &(*head)->prev;
    bool separator = loop_while_spaces(input, i);

    if (!(input[(*i)]))
        return (false);
    if (*i > 0 && is_char_spaces(input[(*i) - 1]))
        separator = true;
    if (is_char_backstick(input[(*i)])) {
        get_quoted_arg(&((*cur)->cmd_list), separator, input, i);
        return (true);
    }
    if (is_char_splitter(input[(*i)])) {
        if (get_splitter(head, error, input, i))
            return (true);
    }
    if (is_char_redirection(input[(*i)]))
        get_redirection(&((*cur)->cmd_list), error, input, i);
    else
        get_unquoted_arg(&((*cur)->cmd_list), separator, input, i);
    apply_wildcards_changes((*head)->prev);
    return (true);
}

parse_list_t *parse_input(const char *input, error_parse_t *error)
{
    parse_list_t *parsing_list = NULL;
    size_t i = 0;

    if (!input || !check_unmatched_backticks(input, error))
        return (NULL);
    add_parsed_list_node(&parsing_list);
    if (!parsing_list)
        return (NULL);
    add_cmd_list_node(&(parsing_list)->cmd_list);
    while (input[i] && !(*error)) {
        if (!parse_each_argument(&parsing_list, error, input, &i))
            break;
    }
    return (parsing_list);
}