/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Gets a splitter and adds a parsed_list node.
*/

#include "my.h"
#include "mysh_parsing.h"

static bool shift_to_next_arg(const splitter_type_t splitter_type,
                                const char *input, size_t *i)
{
    if (splitter_type == 0)
        return (false);
    *i += my_strlen(splitters[splitter_type - 1]);
    loop_while_spaces(input, i);
    return (true);
}

static bool set_splitter_alterations(parsed_input_list_t **head,
                                    const splitter_type_t splitter_type,
                                    const char c)
{
    if (!((*head)->cmd_list->args) || !c || is_char_splitter(c))
        return (true);
    add_parsed_list_node(head);
    add_cmd_list_node(&((*head)->prev->cmd_list));
    (*head)->prev->splitter = splitter_type;
    return (true);
}

static bool inv_null_checker(parsed_input_list_t *cur_node,
                            error_parse_t *error,
                            const splitter_type_t splitter_type,
                            const char c)
{
    if ((splitter_type == OR && (!cur_node->cmd_list
        || !cur_node->cmd_list->args || !c || is_char_splitter(c)))) {
        *error = INVALID_NULL_COMMAND;
        return (true);
    }
    if ((splitter_type == AND && cur_node->cmd_list
        && cur_node->cmd_list->args && (!c || is_char_splitter(c)))) {
        *error = INVALID_NULL_COMMAND;
        return (true);
    }
    return (false);
}

bool get_splitter(parsed_input_list_t **head, error_parse_t *error,
                    const char *input, size_t *i)
{
    int size = 0;
    splitter_type_t splitter_type = get_splitter_enum(&input[(*i)], &size);

    if (!shift_to_next_arg(splitter_type, input, i))
        return (false);
    if (inv_null_checker((*head)->prev, error, splitter_type, input[*i]))
        return (true);
    return (set_splitter_alterations(head, splitter_type, input[*i]));
}