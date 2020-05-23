/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** Adds a new variable to the var.
*/

#include "my.h"
#include "mysh_variables.h"

bool remove_var_from_var_list(var_list_t **var_list, const char *var_name)
{
    var_list_t *variable = NULL;

    if (!(*var_list) || !var_name)
        return (false);
    variable = get_var_in_var_list(*var_list, var_name);
    if (!variable)
        return (false);
    if (variable == *var_list) {
        *var_list = (*var_list)->next;
        if (variable == *var_list) {
            free_var_node(variable);
            *var_list = NULL;
            return (true);
        }
    }
    variable->prev->next = variable->next;
    variable->next->prev = variable->prev;
    free_var_node(variable);
    return (true);
}