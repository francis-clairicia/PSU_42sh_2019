/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** Parses the given input into a doubly circular linked list.
*/

#include <stdbool.h>
#include <stdlib.h>
#include "my.h"
#include "mysh_parsing.h"

static bool set_separator(indicator_t *indic)
{
    indic->separator = loop_while_spaces(indic->input, &indic->i);
    if (!(indic->input[indic->i]))
        return (false);
    if (indic->i > 0 && is_char_spaces(indic->input[indic->i - 1]))
        indic->separator = true;
    return (true);
}

static bool parse_each_argument(parse_list_t **head, indicator_t *indic,
                                error_parse_t *error)
{
    cmd_list_t **cur_cmd_list = &(*head)->prev->cmd_list;

    if (!set_separator(indic))
        return (false);
    if (check_for_backtick_elem(cur_cmd_list, indic))
        return (true);
    if (check_for_splitter_elem(head, indic, error))
        return (true);
    if (!check_for_redirection_elem(cur_cmd_list, indic, error))
        get_unquoted_arg(cur_cmd_list, indic);
    if (indic->last_quotation == WAS_UNQUOTED)
        apply_wildcards_changes((*head)->prev);
    return (true);
}

parse_list_t *parse_input(const char *input, error_parse_t *error)
{
    parse_list_t *parsing_list = NULL;
    indicator_t indic = {.input = input, .i = 0,
                    .separator = false, .last_quotation = NONE};

    if (!input || !check_unmatched_backticks(input, error))
        return (NULL);
    add_parsed_list_node(&parsing_list);
    if (!parsing_list)
        return (NULL);
    add_cmd_list_node(&(parsing_list)->cmd_list);
    while (indic.input[indic.i] && !(*error)) {
        if (!parse_each_argument(&parsing_list, &indic, error))
            break;
    }
    return (parsing_list);
}