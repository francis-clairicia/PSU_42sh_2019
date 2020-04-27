/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Gets a splitter and adds a parsed_list node.
*/

#include "my.h"
#include "parsing.h"

bool get_splitter(parsed_input_list_t **head, const char *input, size_t *i)
{
    ssize_t splitter_type = get_splitter_enum(&input[(*i)]);

    if (splitter_type <= 0)
        return (false);
    *i += my_strlen(splitters[splitter_type - 1]);
    loop_while_spaces(input, i);
    if (!((*head)->cmd_list->args) || !input[(*i)]
        || is_char_splitter(input[*i]))
        return (true);
    ADD_PARSE_NODE(head, parsed_input_list_t);
    ADD_PARSE_NODE(&((*head)->prev->cmd_list), cmd_list_t);
    (*head)->prev->splitter = splitter_type;
    return (true);
}