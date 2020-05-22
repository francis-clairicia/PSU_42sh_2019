/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Adds nodes to certain lists.
*/

#include <string.h>
#include <stdlib.h>
#include "mysh_parsing.h"

arguments_t *add_arg_list_node_index(arguments_t **head,
                                    arguments_t *previous)
{
    arguments_t *node = NULL;

    if (!head || !previous)
        return (NULL);
    node = malloc(sizeof(arguments_t));
    if (!node)
        return (NULL);
    memset(node, 0, sizeof(arguments_t));
    if (!(*head)) {
        *head = node;
        node->next = *head;
        node->prev = *head;
    } else {
        node->next = previous->next;
        node->prev = previous;
        previous->next->prev = node;
        previous->next = node;
    }
    return (node);
}

void add_arg_list_node(arguments_t **head)
{
    arguments_t *node = NULL;

    if (!head)
        return;
    node = malloc(sizeof(arguments_t));
    if (!node)
        return;
    memset(node, 0, sizeof(arguments_t));
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

void add_cmd_list_node(cmd_list_t **head)
{
    cmd_list_t *node = NULL;

    if (!head)
        return;
    node = malloc(sizeof(cmd_list_t));
    if (!node)
        return;
    memset(node, 0, sizeof(cmd_list_t));
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

void add_parsed_list_node(parsed_input_list_t **head)
{
    parsed_input_list_t *node = NULL;

    if (!head)
        return;
    node = malloc(sizeof(parsed_input_list_t));
    if (!node)
        return;
    memset(node, 0, sizeof(parsed_input_list_t));
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
