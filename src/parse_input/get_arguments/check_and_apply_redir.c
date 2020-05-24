/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** Checks for errors due to redirections.
*/

#include "mysh_parsing.h"

void set_redir_type(cmd_list_t **head, parse_error_t *error,
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

void check_redir_file_set(const cmd_list_t *cmd, parse_error_t *error,
                        const redirection_type_t redir_type,
                        const char c)
{
    if (!(redir_type & PIPE)) {
        if ((IS_INPUT(redir_type) && !(cmd->redir_input))
            || (IS_OUTPUT(redir_type) && !(cmd->redir_output))) {
            *error = MISSING_NAME_FOR_REDIRECT;
            return;
        }
    }
    if (((!(cmd->redir_output_type & PIPE) && !cmd->args && c == '\0')
        || ((cmd->redir_output_type & PIPE)
        && (!cmd->args || IS_CHAR_SPLITTER(c) || c == '\0' )))) {
        *error = INVALID_NULL_COMMAND;
        return;
    }
}
