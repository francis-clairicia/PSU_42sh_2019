/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** Removes an arg node from an arg list with pointer reorganization.
*/

#include <string.h>
#include "mysh_parsing.h"

bool remove_node_from_arg_list_index(arguments_t **head, arguments_t *to_rm)
{
    bool solo_node = false;

    if (!head || !(*head) || !to_rm)
        return (false);
    if ((to_rm == *head) && *head != (*head)->prev)
        solo_node = true;
    to_rm->prev->next = to_rm->next;
    to_rm->next->prev = to_rm->prev;
    free_arg_node(to_rm);
    if (solo_node)
        *head = (*head)->next;
    return (true);
}
