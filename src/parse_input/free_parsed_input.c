/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Frees the parsed input nodes and lists.
*/

#include <stdlib.h>
#include "parsing.h"

static void free_args_list(arguments_t *head)
{
    arguments_t *final = NULL;
    arguments_t *tmp = NULL;

    if (!head)
        return;
    final = head;
    tmp = head;
    do {
        head = head->next;
        if (tmp->arg)
            free(tmp->arg);
        if (tmp)
            free(tmp);
        tmp = head;
    } while (tmp != final);
}

static void free_cmd_node(cmd_list_t *node)
{
    if (!node)
        return;
    free_args_list(node->args);
    if (node->redir_name)
        free(node->redir_name);
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

void free_parsed_input_node(parsed_input_list_t *node)
{
    if (!node)
        return;
    free_cmd_list(node->cmd_list);
    free(node);
}

void free_parsed_input_list(parsed_input_list_t *head)
{
    parsed_input_list_t *final = NULL;
    parsed_input_list_t *tmp = NULL;

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