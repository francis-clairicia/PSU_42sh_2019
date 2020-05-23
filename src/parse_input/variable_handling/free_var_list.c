/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** Free's an var_list.
*/

#include <stdlib.h>
#include "mysh_variables.h"

void free_var_node(var_list_t *node)
{
    if (!node)
        return;
    if (node->var_name)
        free(node->var_name);
    if (node->var_value)
        free(node->var_value);
    free(node);
}

void free_var_list(var_list_t *var_list)
{
    var_list_t *save = NULL;
    var_list_t *tmp = NULL;

    if (!var_list)
        return;
    save = var_list;
    tmp = var_list;
    do {
        var_list = var_list->next;
        free_var_node(tmp);
        tmp = var_list;
    } while (tmp && tmp != save);
}