/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** get_var_value.c
*/

#include "minishell.h"

char *get_var_value(char * const *envp, int index)
{
    int equal_index = 0;

    if (envp == NULL)
        return (NULL);
    if (index < 0 || index >= my_array_len(envp))
        return (NULL);
    equal_index = my_strchr_index(envp[index], '=');
    if (equal_index < 0)
        return (NULL);
    return (&(envp[index][equal_index + 1]));
}