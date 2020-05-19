/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** Creates an env_list from an array.
*/

#include <stdbool.h>
#include <stdlib.h>
#include "my.h"
#include "mysh_env.h"

static bool assert_node_variables(env_list_t *node, const char *envg_line,
                                    const size_t index)
{
    if (!node)
        return (false);
    node->var_name = my_strdup_until_list_c(envg_line, "=");
    if (!node->var_name)
        return (false);
    node->var_value = my_strdup(&envg_line[index + 1]);
    if (!node->var_value)
        return (false);
    return (true);
}

static bool add_node(env_list_t **list, const char *envg_line)
{
    register size_t index = 0;
    env_list_t *node = NULL;

    if (!envg_line)
        return (false);
    while (envg_line[index] && envg_line[index] != '=')
        index += 1;
    if (!envg_line[index])
        return (false);
    node = malloc(sizeof(env_list_t));
    if (!node)
        return (false);
    node->next = *list;
    node->prev = (*list)->prev;
    (*list)->prev->next = node;
    (*list)->prev = node;
    if (!assert_node_variables(node, envg_line, index))
        return (false);
    return (true);
}

static bool add_first_node(env_list_t **list, const char *envg_line)
{
    register size_t index = 0;
    env_list_t *node = NULL;

    if (!envg_line)
        return (false);
    while (envg_line[index] && envg_line[index] != '=')
        index += 1;
    if (!envg_line[index])
        return (false);
    node = malloc(sizeof(env_list_t));
    if (!node)
        return (false);
    node->next = node;
    node->prev = node;
    *list = node;
    if (!assert_node_variables(node, envg_line, index))
        return (false);
    return (true);
}

static bool assert_new_node(env_list_t **env_list, const char *envg_line)
{
    if (!(*env_list)) {
        if (!add_first_node(env_list, envg_line))
            return (false);
    }
    else {
        if (!add_node(env_list, envg_line))
            return (false);
    }
    return (true);
}

env_list_t *create_env_list_from_array(const char * const *envg)
{
    register size_t index = 0;
    env_list_t *env_list = NULL;

    if (!envg)
        return (NULL);
    while (envg[index]) {
        if (!assert_new_node(&env_list, envg[index])) {
            free_env_list(env_list);
            return (NULL);
        }
        index += 1;
    }
    return (env_list);
}