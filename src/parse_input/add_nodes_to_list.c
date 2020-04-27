/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Adds nodes to certain lists.
*/

#include <stdlib.h>
#include "parsing.h"

void add_node_to_arg_list(arguments_t **head)
{
    arguments_t *node = NULL;

    if (!head)
        return;
    node = malloc(sizeof(arguments_t));
    if (!node)
        return;
    node->arg = NULL;
    if (!(*head)) {
        *head = node;
        node->next = *head;
        node->prev = *head;
    } else {
        node->next = (*head);
        node->prev = (*head)->prev;
        (*head)->prev->next = node;
        (*head)->prev = node;
    }
}

void add_node_to_cmd_list(cmd_list_t **head)
{
    cmd_list_t *node = NULL;

    if (!head)
        return;
    node = malloc(sizeof(cmd_list_t));
    if (!node)
        return;
    *node = (cmd_list_t){.args = NULL, .redir_name = NULL, .redir_type = NONE};
    if (!(*head)) {
        *head = node;
        node->next = *head;
        node->prev = *head;
    } else {
        node->next = (*head);
        node->prev = (*head)->prev;
        (*head)->prev->next = node;
        (*head)->prev = node;
    }
}

void add_node_to_parsed_list(parsed_input_list_t **head)
{
    parsed_input_list_t *node = NULL;

    if (!head)
        return;
    node = malloc(sizeof(parsed_input_list_t));
    if (!node)
        return;
    *node = (parsed_input_list_t){.cmd_list = NULL, .splitter = NONE};
    if (!(*head)) {
        node->next = node;
        node->prev = node;
        *head = node;
    } else {
        node->next = (*head);
        node->prev = (*head)->prev;
        (*head)->prev->next = node;
        (*head)->prev = node;
    }
}