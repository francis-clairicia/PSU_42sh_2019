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
    indic->separator = LOOP_SPACES(indic->input, &indic->i);
    if (!(indic->input[indic->i]))
        return (false);
    if (indic->i > 0 && IS_CHAR_SPACES(indic->input[indic->i - 1]))
        indic->separator = true;
    return (true);
}

static void apply_last_elem_changes(parse_list_t **head, indicator_t *indic,
                                    shell_t *shell, parse_error_t *error)
{
    if ((*error) == NONE && indic->last_quotation != WAS_SINGLE
        && indic->last_quotation != WAS_MAGIC)
        apply_vars_to_last_elem((*head)->prev, shell, error);
    if ((*error) == NONE && indic->last_quotation == WAS_UNQUOTED
        && indic->last_quotation != WAS_MAGIC)
        apply_wildcards_changes((*head)->prev);
}

static bool parse_each_argument(parse_list_t **head, indicator_t *indic,
                                shell_t *shell, parse_error_t *error)
{
    cmd_list_t **cur_cmd_list = &(*head)->prev->cmd_list;
    bool found_arg = false;

    if (!set_separator(indic))
        return (false);
    check_for_quoted_elem(&found_arg, cur_cmd_list, indic);
    check_for_splitter_elem(&found_arg, head, indic, error);
    check_for_redirection_elem(&found_arg, cur_cmd_list, indic, error);
    check_for_unquoted_elem(&found_arg, cur_cmd_list, indic);
    apply_last_elem_changes(head, indic, shell, error);
    check_for_magic_quotes(&found_arg, shell, cur_cmd_list, indic);
    return (true);
}

parse_list_t *parse_input(shell_t *shell, const char *input,
                            parse_error_t *error)
{
    parse_list_t *parsing_list = NULL;
    indicator_t indic = {.input = input, .i = 0,
                    .separator = false, .last_quotation = NONE};

    if (!input || !shell || !check_unmatched_chars(input, error))
        return (NULL);
    add_parsed_list_node(&parsing_list);
    if (!parsing_list)
        return (NULL);
    add_cmd_list_node(&(parsing_list)->cmd_list);
    while (indic.input[indic.i] && !(*error)) {
        if (!parse_each_argument(&parsing_list, &indic, shell, error))
            break;
    }
    return (parsing_list);
}