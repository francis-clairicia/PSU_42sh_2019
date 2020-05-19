/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** Gets a pointer onto an env_list node.
*/

#include "my.h"
#include "mysh_env.h"

env_list_t *get_var_in_env_list(env_list_t *head, const char *var_name)
{
    env_list_t *tmp = NULL;

    if (!head)
        return (NULL);
    tmp = head;
    do {
        if (!my_strcmp(tmp->var_name, var_name))
            return (tmp);
        tmp = tmp->next;
    } while (tmp != head);
    return (NULL);
}