/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Frees the parsed input nodes and lists.
*/

#include <stdlib.h>
#include "mysh_parsing.h"

void free_arg_node(arguments_t *node)
{
    if (!node)
        return;
    if (node->arg)
        free(node->arg);
    if (node)
        free(node);
}

void free_args_list(arguments_t *head)
{
    arguments_t *final = NULL;
    arguments_t *tmp = NULL;

    if (!head)
        return;
    final = head;
    tmp = head;
    do {
        head = head->next;
        free_arg_node(tmp);
        tmp = head;
    } while (tmp != final);
}