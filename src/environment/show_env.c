/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** Shows the env.
*/

#include "my.h"
#include "mysh_env.h"

void show_env(env_list_t *head)
{
    env_list_t *tmp = NULL;

    if (!head)
        return;
    tmp = head;
    do {
        if (tmp->var_name)
            my_printf("%s=%s\n", tmp->var_name, tmp->var_value);
        tmp = tmp->next;
    } while (tmp != head);
}