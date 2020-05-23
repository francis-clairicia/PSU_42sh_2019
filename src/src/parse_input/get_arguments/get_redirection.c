/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** Gets a redirection and its arguments.
*/

#include "my.h"
#include "mysh_parsing.h"

static void add_unquoted_redir(char **redir_name, indicator_t *indic)
{
    char *tmp = NULL;

    tmp = my_strdup_list_i(&indic->input[indic->i], all_splitters, &indic->i);
    (*redir_name) = my_strcat_malloc((*redir_name), tmp, 1, 1);
}

static void add_quoted_redir(char **redir_name, indicator_t *indic,
                            const char quote)
{
    char *tmp = NULL;

    indic->i += 1;
    tmp = my_strdup_char_i(&indic->input[indic->i], quote, &indic->i);
    (*redir_name) = my_strcat_malloc((*redir_name), tmp, 1, 1);
    indic->i += 1;
}

static void redir_file(cmd_list_t **head, indicator_t *indic,
                        const ssize_t redir_type)
{
    char **redir_output = &(*head)->prev->redir_output;
    char **redir_input = &(*head)->prev->redir_input;
    char **redir_name = NULL;
    char quote = '\0';

    indic->separator = false;
    while (!indic->separator && indic->input[indic->i]) {
        redir_name = (IS_INPUT(redir_type) ? redir_input : redir_output);
        quote = is_char_backtick(indic->input[indic->i]);
        if (quote)
            add_quoted_redir(redir_name, indic, quote);
        else
            add_unquoted_redir(redir_name, indic);
        indic->separator = loop_while_spaces(indic->input, &indic->i);
    }
}

void get_redirection(cmd_list_t **head, indicator_t *indic,
                        error_parse_t *error)
{
    redirection_type_t redir_type = NONE;
    int size = 0;
    char c = '\0';

    redir_type = get_redirection_enum(&indic->input[indic->i], &size);
    if (redir_type == NONE) {
        indic->i += 1;
        return;
    }
    indic->i += size;
    loop_while_spaces(indic->input, &indic->i);
    set_redir_type(head, error, redir_type);
    if (*error != NONE)
        return;
    if (!(redir_type & PIPE))
        redir_file(head, indic, redir_type);
    loop_while_spaces(indic->input, &indic->i);
    c = indic->input[indic->i];
    check_redir_file_set((*head)->prev, error, redir_type, c);
    if (!(*error) && (redir_type & PIPE))
        add_cmd_list_node(head);
}
