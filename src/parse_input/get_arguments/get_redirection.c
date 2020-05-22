/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** Gets a redirection and its arguments.
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
