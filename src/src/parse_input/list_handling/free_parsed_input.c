/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** Frees the parsed input nodes and lists.
*/

#include <stdlib.h>
#include "mysh_parsing.h"

static void free_cmd_node(cmd_list_t *node)
{
    if (!node)
        return;
    free_args_list(node->args);
    if (node->redir_input)
        free(node->redir_input);
    if (node->redir_output)
        free(node->redir_output);
    free(node);
}

static void free_cmd_list(cmd_list_t *head)
{
    cmd_list_t *final = NULL;
    cmd_list_t *tmp = NULL;

    if (!head)
        return;
    final = head;
    tmp = head;
    do {
        head = head->next;
        free_cmd_node(tmp);
        tmp = head;
    } while (tmp != final);
}

static void free_parsed_input_node(parse_list_t *node)
{
    if (!node)
        return;
    free_cmd_list(node->cmd_list);
    free(node);
}

void free_parse_list(parse_list_t *head)
{
    parse_list_t *final = NULL;
    parse_list_t *tmp = NULL;

    if (!head)
        return;
    final = head;
    tmp = head;
    do {
        head = head->next;
        free_parsed_input_node(tmp);
        tmp = head;
    } while (tmp != final);
}