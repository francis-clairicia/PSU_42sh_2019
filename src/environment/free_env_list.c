/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** Free's an env_list.
*/

#include <stdlib.h>
#include "mysh_env.h"

void free_env_node(env_list_t *node)
{
    if (!node)
        return;
    if (node->var_name)
        free(node->var_name);
    if (node->var_value)
        free(node->var_value);
    free(node);
}

void free_env_list(env_list_t *env_list)
{
    env_list_t *save = NULL;
    env_list_t *tmp = NULL;

    if (!env_list)
        return;
    save = env_list;
    tmp = env_list;
    do {
        env_list = env_list->next;
        free_env_node(tmp);
        tmp = env_list;
    } while (tmp && tmp != save);
}