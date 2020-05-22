/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** create_variable.c
*/

#include "minishell.h"

char *create_variable(char const *variable, char const *value)
{
    int len_var = my_strlen(variable);
    int len_value = my_strlen(value);
    int size = len_var + 1 + len_value;
    char *var = NULL;

    if (len_var == 0)
        return (NULL);
    var = malloc(sizeof(char) * (size + 1));
    if (var != NULL) {
        my_memset(var, 0, size + 1);
        my_strcat(var, variable);
        my_strcat(var, "=");
        my_strcat(var, value);
    }
    return (var);
}