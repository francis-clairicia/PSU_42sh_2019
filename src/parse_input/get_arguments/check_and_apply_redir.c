/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** check_and_apply_redir.c
*/

#include "mysh_parsing.h"

void set_redir_type(cmd_list_t **head, error_parse_t *error,
                    const redirection_type_t redir_type)
{
    if (IS_INPUT(redir_type)) {
        if ((*head)->prev->redir_input_type != NONE
            || (*head)->prev->prev->redir_output_type & PIPE)
            *error = AMBIGUOUS_INPUT_REDIRECT;
        else
            (*head)->prev->redir_input_type = redir_type;
    } else {
        if ((*head)->prev->redir_output_type != NONE)
            *error = AMBIGUOUS_OUTPUT_REDIRECT;
        else
            (*head)->prev->redir_output_type = redir_type;
    }
}

void check_redir_file_set(const cmd_list_t *cur_cmd, error_parse_t *error,
                        const redirection_type_t redir_type,
                        const char cur_char)
{
    if (!(redir_type & PIPE)) {
        if ((IS_INPUT(redir_type) && !(cur_cmd->redir_input))
            || (IS_OUTPUT(redir_type) && !(cur_cmd->redir_output))) {
            *error = MISSING_NAME_FOR_REDIRECT;
            return;
        }
    }
    if (((cur_cmd->redir_output_type & PIPE)
        && (!cur_cmd->args || is_char_splitter(cur_char)
        || cur_char == '\0'))) {
        *error = INVALID_NULL_COMMAND;
        return;
    }
}
