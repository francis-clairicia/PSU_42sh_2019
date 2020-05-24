/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** Gets a splitter and adds a parsed_list node.
*/

#include "my.h"
#include "mysh_parsing.h"

static bool shift_to_next_arg(const splitter_type_t splitter_type,
                                indicator_t *indic)
{
    if (splitter_type == 0)
        return (false);
    indic->i += my_strlen(splitters[splitter_type - 1]);
    loop_while_spaces(indic->input, &indic->i);
    return (true);
}

static bool set_splitter_alterations(parse_list_t **head,
                                    const splitter_type_t splitter_type,
                                    const char c)
{
    if (!((*head)->cmd_list->args) || !c || is_char_splitter(c))
        return (true);
    (*head)->prev->splitter = splitter_type;
    add_parsed_list_node(head);
    add_cmd_list_node(&((*head)->prev->cmd_list));
    return (true);
}

static bool inv_null_checker(parse_list_t *cur_node,
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

bool get_splitter(parse_list_t **head, indicator_t *indic,
                    error_parse_t *error)
{
    splitter_type_t splitter_type = NONE;
    int size = 0;
    char c = '\0';

    splitter_type = get_splitter_enum(&indic->input[indic->i], &size);
    if (!shift_to_next_arg(splitter_type, indic))
        return (false);
    c = indic->input[indic->i];
    if (inv_null_checker((*head)->prev, error, splitter_type, c))
        return (true);
    return (set_splitter_alterations(head, splitter_type, c));
}