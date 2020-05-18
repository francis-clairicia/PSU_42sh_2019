/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** Gets the size of an env_list.
*/

#include <unistd.h>
#include "mysh_env.h"

size_t get_env_list_size(env_list_t *head)
{
    env_list_t *tmp = NULL;
    size_t size = 0;

    if (!head)
        return (0);
    tmp = head;
    do {
        size += 1;
        tmp = tmp->next;
    } while (tmp != head);
    return (size);
}