/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Adds nodes to certain lists.
*/

#include <stdlib.h>
#include "mysh_parsing.h"

void add_arg_list_node(arguments_t **head)
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

void add_cmd_list_node(cmd_list_t **head)
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

void add_parsed_list_node(parsed_input_list_t **head)
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

void *add_parsing_node(void **head, const size_t size)
{
    void *node = NULL;

    if (!head)
        return (NULL);
    node = malloc(size);
    if (!node)
        return (NULL);
    my_memset(node, 0, size);
    if (!(*head)) {
        GET_ELEM_END(node, size, 16) = (size_t)node;
        GET_ELEM_END(node, size, 8) = (size_t)node;
        *head = node;
    } else {
        GET_ELEM_END(node, size, 16) = (size_t)(*head);
        GET_ELEM_END(node, size, 8) = GET_ELEM_END(head, size, 8);
        GET_ELEM_END(GET_ELEM_END(*head, size, 8), size, 16) = (size_t)node;
        GET_ELEM_END(*head, size, 8) = (size_t)node;
    }
    return (node);
}