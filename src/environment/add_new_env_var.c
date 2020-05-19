/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** Adds a new variable to an env_list.
*/

#include <stdlib.h>
#include "my.h"
#include "mysh_env.h"

static void set_env_node_as_end(env_list_t **head, env_list_t *node)
{
    node->next = *head;
    node->prev = (*head)->prev;
    (*head)->prev->next = node;
    (*head)->prev = node;
}

static void set_env_node_as_head(env_list_t **head, env_list_t *node)
{
    node->next = node;
    node->prev = node;
    *head = node;
}

static bool add_env_node(const char *var_name, const char *var_value,
                            env_list_t **head)
{
    env_list_t *node = NULL;

    node = malloc(sizeof(env_list_t));
    if (!node)
        return (false);
    if (!(*head))
        set_env_node_as_head(head, node);
    else
        set_env_node_as_end(head, node);
    node->var_name = my_strdup(var_name);
    if (!node->var_name && var_name)
        return (false);
    node->var_value = my_strdup(var_value);
    return (!node->var_value && var_value) ? false : true;
}

bool add_new_env_var(env_list_t **env_list, const char *var_name,
                        const char *var_value)
{
    if (!env_list)
        return (false);
    if (!add_env_node(var_name, var_value, env_list))
        return (false);
    return (true);
}