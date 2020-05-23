/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** Adds a new variable to an var_list.
*/

#include <stdlib.h>
#include "my.h"
#include "mysh_variables.h"

static var_list_t *create_node(const char *var_name, const char *var_value)
{
    var_list_t *node = NULL;

    node = malloc(sizeof(var_list_t));
    if (!node)
        return (NULL);
    my_memset(node, 0, sizeof(*node));
    node->next = node;
    node->prev = node;
    node->var_name = my_strdup(var_name);
    if (!node->var_name) {
        free(node);
        return (NULL);
    }
    node->var_value = my_strdup(var_value);
    return (node);
}

bool add_var_to_var_list(var_list_t **var_list, const char *var_name,
                        const char *var_value)
{
    var_list_t *node = NULL;

    if (!var_list)
        return (false);
    node = create_node(var_name, var_value);
    if (!node)
        return (false);
    if (!(*var_list)) {
        *var_list = node;
    } else {
        node->next = *var_list;
        node->prev = (*var_list)->prev;
        (*var_list)->prev->next = node;
        (*var_list)->prev = node;
    }
    return (true);
}