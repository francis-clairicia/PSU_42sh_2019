/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Parses the given input into a doubly circular linked list.
*/

#include <stdbool.h>
#include <stdlib.h>
#include "my.h"
#include "mysh_parsing.h"

static void apply_globbing_to_node(parsed_input_list_t *cur_node,
                                    arguments_t **tmp)
{
    arguments_t *save_tmp = (*tmp)->next;

    if (add_args_for_matching(&cur_node->cmd_list->args, *tmp, (*tmp)->arg)) {
        remove_node_from_arg_list_index(&cur_node->cmd_list->args, *tmp);
        (*tmp) = save_tmp;
    }
}

static void apply_globbing_wild_card(parsed_input_list_t *cur_node)
{
    arguments_t *tmp = NULL;

    if (!cur_node || !(cur_node->cmd_list || !(cur_node->cmd_list->args))
        || (cur_node->cmd_list->args->prev) == (cur_node->cmd_list->args))
        return;
    tmp = cur_node->cmd_list->args->next;
    do {
        if (my_strchr(tmp->arg, '*'))
            apply_globbing_to_node(cur_node, &tmp);
        tmp = tmp->next;
    } while (tmp != cur_node->cmd_list->args);
}

static bool parse_each_argument(parsed_input_list_t **head,
                                error_parse_t *error,
                                const char *input, size_t *i)
{
    parsed_input_list_t **cur = &(*head)->prev;
    bool separator = loop_while_spaces(input, i);

    if (!(input[(*i)]))
        return (false);
    if (is_char_backstick(input[(*i)])) {
        get_quoted_arg(&((*cur)->cmd_list), separator, input, i);
        return (true);
    }
    if (is_char_splitter(input[(*i)])) {
        if (get_splitter(head, error, input, i))
            return (true);
    }
    if (is_char_redirection(input[(*i)]))
        get_redirection(&((*cur)->cmd_list), error, input, i);
    else
        get_unquoted_arg(&((*cur)->cmd_list), separator, input, i);
    apply_globbing_wild_card((*head)->prev);
    return (true);
}

parsed_input_list_t *parse_input(const char *input, error_parse_t *error)
{
    parsed_input_list_t *parsing_list = NULL;
    size_t i = 0;

    if (!input || !check_unmatched_backticks(input, error))
        return (NULL);
    add_parsed_list_node(&parsing_list);
    add_cmd_list_node(&(parsing_list)->cmd_list);
    while (input[i] && !(*error)) {
        if (!parse_each_argument(&parsing_list, error, input, &i))
            break;
    }
    return (parsing_list);
}