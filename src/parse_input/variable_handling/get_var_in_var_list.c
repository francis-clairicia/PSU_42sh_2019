/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** Gets a pointer onto an var_list node.
*/

#include "my.h"
#include "mysh_variables.h"

var_list_t *get_var_in_var_list(var_list_t *head, const char *var_name)
{
    var_list_t *tmp = NULL;

    if (!head)
        return (NULL);
    tmp = head;
    do {
        if (my_str_eq_str(tmp->var_name, var_name))
            return (tmp);
        tmp = tmp->next;
    } while (tmp != head);
    return (NULL);
}
