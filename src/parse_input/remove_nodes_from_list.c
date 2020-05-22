/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Adds nodes to certain lists.
*/

#include <string.h>
#include <stdlib.h>
#include "mysh_parsing.h"

void remove_node_from_arg_list_index(arguments_t **head,
                                    arguments_t *to_rm)
{
    bool solo_node = false;

    if (!head || !(*head) || !to_rm)
        return;
    if (to_rm == *head) {
        if (*head != (*head)->prev)
            solo_node = true;
    }
    to_rm->prev->next = to_rm->next;
    to_rm->next->prev = to_rm->prev;
    free_arg_node(to_rm);
    if (solo_node)
        *head = (*head)->next;;
}
