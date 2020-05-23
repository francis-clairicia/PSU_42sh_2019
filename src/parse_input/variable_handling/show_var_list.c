/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** Shows the var.
*/

#include "my.h"
#include "mysh_variables.h"

void show_var_list(var_list_t *head)
{
    var_list_t *tmp = NULL;

    if (!head)
        return;
    tmp = head;
    do {
        if (tmp->var_name)
            my_printf("%s=%s\n", tmp->var_name, tmp->var_value);
        tmp = tmp->next;
    } while (tmp != head);
}