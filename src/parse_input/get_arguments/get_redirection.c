/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Gets a redirection.
*/

#include "my.h"
#include "parsing.h"

static void redir_file(cmd_list_t **head, const char *input, size_t *i)
{
    char **redir_name = &((*head)->prev->redir_name);
    char quote = is_char_backtick(input[(*i)]);

    if (quote) {
        *i += 1;
        *redir_name = my_strdup_char_i(&input[(*i)], quote, i);
        *i += 1;
    } else
        *redir_name = my_strdup_list_i(&input[(*i)], all_splitters, i);
}

static bool check_pipe_error(cmd_list_t **head, const char c,
                                error_parse_t *error)
{
    if ((*head)->prev->redir_type != NONE
        && (*head)->prev->redir_type != PIPE) {
        (*error) = AMBIGUOUS_OUTPUT_REDIRECT;
        return (false);
    } else if (!((*head)->prev->prev->args) || !c || is_char_stopper(c)) {
        (*error) = INVALID_NULL_COMMAND;
        return (false);
    }
    return (true);
}

static void check_direct_redir_error(cmd_list_t **head,
                                    const ssize_t redir_type,
                                    const char c,
                                    error_parse_t *error)
{
    if (redir_type != PIPE && !(*head)->prev->args
        && (!c || is_char_stopper(c))) {
        (*error) = MISSING_NAME_FOR_REDIRECT;
    }
}

static bool check_for_redirect_error(cmd_list_t **head,
                                    const ssize_t redir_type,
                                    const char c,
                                    error_parse_t *error)
{
    if (redir_type == PIPE) {
        if (!check_pipe_error(head, c, error))
            return (false);
    } else if (!c || is_char_stopper(c)) {
        (*error) = MISSING_NAME_FOR_REDIRECT;
        return (false);
    }
    return (true);
}

void get_redirection(cmd_list_t **head, error_parse_t *error,
                    const char *input, size_t *i)
{
    ssize_t redir_type = get_redirection_enum(&input[(*i)]);

    if (redir_type <= 0) {
        *i += 1;
        return;
    }
    *i += my_strlen(redirections[redir_type - 1]);
    loop_while_spaces(input, i);
    check_for_redirect_error(head, redir_type, input[(*i)], error);
    if ((*error) != NONE)
        return;
    (*head)->prev->redir_type = redir_type;
    redir_type == PIPE ? ADD_PARSE_NODE(head, cmd_list_t) : redir_file(head, input, i);
    check_direct_redir_error(head, redir_type, input[(*i)], error);
}