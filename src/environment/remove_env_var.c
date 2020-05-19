/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** Adds a new variable to the env.
*/

#include "my.h"
#include "mysh_env.h"

bool remove_env_var(env_list_t **env_list, const char *var_name)
{
    size_t size = get_env_list_size(*env_list);
    env_list_t *variable = NULL;

    if (!(*env_list) || !var_name)
        return (false);
    variable = get_var_in_env_list(*env_list, var_name);
    if (!variable)
        return (false);
    if (variable == *env_list) {
        *env_list = (*env_list)->next;
        if (variable == *env_list) {
            free_env_node(variable);
            *env_list = NULL;
            return (true);
        }
    }
    variable->prev->next = variable->next;
    variable->next->prev = variable->prev;
    free_env_node(variable);
    return (true);
}