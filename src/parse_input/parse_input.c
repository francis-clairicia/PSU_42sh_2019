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

static bool parse_each_argument(parsed_input_list_t **head,
                                error_parse_t *error,
                                const char *input, size_t *i)
{
    parsed_input_list_t **cur = (parsed_input_list_t **)&DCLL_PREV(*head);
    bool separator = loop_while_spaces(input, i);

    if (!(input[(*i)]))
        return (false);
    if (is_char_backstick(input[(*i)])) {
        get_quoted_arg(&((*cur)->cmd_list), separator, input, i);
        return (true);
    }
    if (is_char_splitter(input[(*i)])) {
        if (get_splitter(head, input, i))
            return (true);
    }
    if (is_char_redirection(input[(*i)]))
        get_redirection(&((*cur)->cmd_list), error, input, i);
    else
        get_unquoted_arg(&((*cur)->cmd_list), separator, input, i);
    return (true);
}

parsed_input_list_t *parse_input(const char *input, error_parse_t *error)
{
    parsed_input_list_t *parsing_list = NULL;
    size_t i = 0;

    if (!input)
        return (NULL);
    DCLL_ADD(&parsing_list, sizeof(parsed_input_list_t), free_parsed_input);
    DCLL_ADD(&(parsing_list->cmd_list), sizeof(cmd_list_t), free_cmd);
    while (input[i] && !(*error)) {
        if (!parse_each_argument(&parsing_list, error, input, &i))
            break;
    }
    return (parsing_list);
}