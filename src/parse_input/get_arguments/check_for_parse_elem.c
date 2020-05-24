/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** check_for_parse_elem.c
*/

#include "mysh_parsing.h"

bool check_for_backtick_elem(bool *found_arg, cmd_list_t **cur_cmd_list,
                            indicator_t *indic)
{
    if (!(*found_arg) && is_char_backtick(indic->input[indic->i])) {
        get_quoted_arg(cur_cmd_list, indic);
        (*found_arg) = true;
        return (true);
    }
    return (false);
}

bool check_for_splitter_elem(bool *found_arg, parse_list_t **head,
                            indicator_t *indic, error_parse_t *error)
{
    if (!(*found_arg) && is_char_splitter(indic->input[indic->i])) {
        if (get_splitter(head, indic, error)) {
            (*found_arg) = true;
            return (true);
        }
    }
    return (false);
}

bool check_for_redirection_elem(bool *found_arg, cmd_list_t **cur_cmd_list,
                            indicator_t *indic, error_parse_t *error)
{
    if (!(*found_arg) && is_char_redirection(indic->input[indic->i])) {
        get_redirection(cur_cmd_list, indic, error);
        (*found_arg) = true;
        return (true);
    }
    return (false);
}

void check_for_unquoted_elem(const bool found_arg, cmd_list_t **cur_cmd_list,
                            indicator_t *indic)
{
    if (!found_arg)
        get_unquoted_arg(cur_cmd_list, indic);
}
