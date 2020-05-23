/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** check_for_parse_elem.c
*/

#include "mysh_parsing.h"

bool check_for_backtick_elem(cmd_list_t **cur_cmd_list, indicator_t *indic)
{
    if (is_char_backtick(indic->input[indic->i])) {
        get_quoted_arg(cur_cmd_list, indic);
        return (true);
    }
    return (false);
}

bool check_for_splitter_elem(parse_list_t **head, indicator_t *indic,
                            error_parse_t *error)
{
    if (is_char_splitter(indic->input[indic->i])) {
        if (get_splitter(head, indic, error))
            return (true);
    }
    return (false);
}

bool check_for_redirection_elem(cmd_list_t **cur_cmd_list, indicator_t *indic,
                                error_parse_t *error)
{
    if (is_char_redirection(indic->input[indic->i])) {
        get_redirection(cur_cmd_list, indic, error);
        return (true);
    }
    return (false);
}
