/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** check_for_parse_elem.c
*/

#include "mysh_parsing.h"

void check_for_quoted_elem(bool *found_arg, cmd_list_t **cur_cmd_list,
                            indicator_t *indic)
{
    if (!(*found_arg) && IS_CHAR_ARGUMENT_QUOTES(indic->input[indic->i])) {
        get_quoted_arg(cur_cmd_list, indic);
        (*found_arg) = true;
    }
}

void check_for_unquoted_elem(bool *found_arg, cmd_list_t **cur_cmd_list,
                            indicator_t *indic)
{
    if (!(*found_arg) && !IS_CHAR_STOPPER(indic->input[indic->i])) {
        get_unquoted_arg(cur_cmd_list, indic);
        (*found_arg) = true;
    }
}
