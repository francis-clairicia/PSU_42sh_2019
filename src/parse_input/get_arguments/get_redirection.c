/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Gets a redirection.
*/

#include "my.h"
#include "mysh_parsing.h"

static void add_unquoted_redir(char **redir_name, const char *input,
                                size_t *i)
{
    char *tmp = NULL;

    tmp = my_strdup_list_i(&input[(*i)], all_splitters, i);
    (*redir_name) = my_strcat_malloc((*redir_name), tmp, 1, 1);
}

static void add_quoted_redir(char **redir_name, const char quote,
                            const char *input, size_t *i)
{
    char *tmp = NULL;

    *i += 1;
    tmp = my_strdup_char_i(&input[(*i)], quote, i);
    (*redir_name) = my_strcat_malloc((*redir_name), tmp, 1, 1);
    *i += 1;
}

static void redir_file(cmd_list_t **head, const ssize_t redir_type,
                        const char *input, size_t *i)
{
    char **redir_output = &(*head)->prev->redir_output;
    char **redir_input = &(*head)->prev->redir_input;
    char **redir_name = NULL;
    char quote = '\0';
    bool separator = false;

    while (!separator && input[(*i)]) {
        redir_name = (IS_INPUT(redir_type) ? redir_input : redir_output);
        quote = is_char_backstick(input[(*i)]);
        if (quote)
            add_quoted_redir(redir_name, quote, input, i);
        else
            add_unquoted_redir(redir_name, input, i);
        separator = loop_while_spaces(input, i);
    }
}

static void set_redir_type(cmd_list_t **head, error_parse_t *error,
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

static void check_redir_file_set(const cmd_list_t *cur_cmd,
                                error_parse_t *error,
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
    if (((cur_cmd->redir_output_type & PIPE) && (!cur_cmd->args || is_char_splitter(cur_char) || cur_char == '\0'))) {
        *error = INVALID_NULL_COMMAND;
        return;
    }
}

void get_redirection(cmd_list_t **head, error_parse_t *error,
                    const char *input, size_t *i)
{
    int size = 0;
    redirection_type_t redir_type = get_redirection_enum(&input[(*i)], &size);

    if (redir_type == NONE) {
        *i += 1;
        return;
    }
    *i += size;
    loop_while_spaces(input, i);
    set_redir_type(head, error, redir_type);
    if (*error != NONE)
        return;
    if (!(redir_type & PIPE))
        redir_file(head, redir_type, input, i);
    loop_while_spaces(input, i);
    check_redir_file_set((*head)->prev, error, redir_type, input[*i]);
    if (!(*error) && (redir_type & PIPE))
        add_cmd_list_node(head);
}
