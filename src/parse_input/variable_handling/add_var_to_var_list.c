/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** Adds a new variable to an var_list.
*/

#include <stdlib.h>
#include "my.h"
#include "mysh_variables.h"

static bool add_node(var_list_t **head, const char *var_name,
                        const char *var_value)
{
    var_list_t *node = NULL;

    if (!(*head))
        return (false);
    node = malloc(sizeof(var_list_t));
    if (!node)
        return (false);
    node->next = *head;
    node->prev = (*head)->prev;
    (*head)->prev->next = node;
    (*head)->prev = node;
    node->var_name = my_strdup(var_name);
    if (!node->var_name)
        return (false);
    node->var_value = my_strdup(var_value);
    return (true);
}

static bool add_first_node(var_list_t **head, const char *var_name,
                            const char *var_value)
{
    var_list_t *node = NULL;

    node = malloc(sizeof(var_list_t));
    if (!node)
        return (false);
    node->next = node;
    node->prev = node;
    *head = node;
    node->var_name = my_strdup(var_name);
    if (!node->var_name)
        return (false);
    node->var_value = my_strdup(var_value);
    return (true);
}

bool add_var_to_var_list(var_list_t **var_list, const char *var_name,
                        const char *var_value)
{
    if (!var_list)
        return (false);
    if (!(*var_list)) {
        if (!add_first_node(var_list, var_name, var_value))
            return (false);
    } else {
        if (!add_node(var_list, var_name, var_value))
            return (false);
    }
    return (true);
}