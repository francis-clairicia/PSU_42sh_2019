/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Gets a redirection.
*/

#include "my.h"
#include "mysh_parsing.h"

static void redir_file(cmd_list_t **head, const char *input, size_t *i)
{
    char **redir_name = NULL;
    char quote = '\0';
    bool separator = false;
    char *tmp = NULL;

    while (!separator && input[(*i)]) {
        redir_name = &((cmd_list_t *)DCLL_PREV(*head))->redir_name;
        quote = is_char_backstick(input[(*i)]);
        if (quote) {
            *i += 1;
            tmp = my_strdup_char_i(&input[(*i)], quote, i);
            *redir_name = my_strcat(*redir_name, tmp, 1, 1);
            *i += 1;
        } else {
            tmp = my_strdup_list_i(&input[(*i)], all_splitters, i);
            *redir_name = my_strcat(*redir_name, tmp, 1, 1);
        }
        separator = loop_while_spaces(input, i);
    }
}

static bool check_pipe_error(cmd_list_t **head, const char c,
                                error_parse_t *error)
{
    if (DCLL_PREV_C(*head, cmd_list_t *)->redir_type != NONE &&
        DCLL_PREV_C(*head, cmd_list_t *)->redir_type != PIPE) {
        (*error) = AMBIGUOUS_OUTPUT_REDIRECT;
        return (false);
    } else if (!c || is_char_stopper(c) ||
        !DCLL_PREV_C(DCLL_PREV_C(*head, cmd_list_t *), cmd_list_t *)->args) {
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
    if (redir_type != PIPE && !DCLL_PREV_C(*head, cmd_list_t *)->args
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
    DCLL_PREV_C(*head, cmd_list_t *)->redir_type = redir_type;
    if (redir_type == PIPE)
        DCLL_ADD(head, sizeof(cmd_list_t), free_cmd);
    else
        redir_file(head, input, i);
    check_direct_redir_error(head, redir_type, input[(*i)], error);
}