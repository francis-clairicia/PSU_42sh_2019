/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** replace_var_call_by_var.c
*/

#include <stdlib.h>
#include "my.h"
#include "mysh_parsing.h"

static void reset_pointers(char **str, char **tmp)
{
    if (*str)
        free(*str);
    (*str) = (*tmp);
    *tmp = NULL;
}

static bool can_replace_variables(char **str, const char *var_call,
                                    const char *var_replace)
{
    if (!str || !(*str))
        return (false);
    if (!var_call || !var_replace)
        return (false);
    if (!my_strcmp(var_call, var_replace))
        return (false);
    return (true);
}

static char *set_new_var(const char *str, const size_t index,
                    const int size_call, const int size_replace)
{
    char *tmp = NULL;
    size_t size = 0;

    size = GET_SIZE_REPLACED(str, index, size_call, size_replace);
    tmp = calloc(size + 1, sizeof(char));
    return (tmp);
}

bool replace_var_call_by_var(char **str, const char *var_call,
                            const char *var_replace)
{
    const int size_call = my_strlen(var_call);
    const int size_replace = my_strlen(var_replace);
    size_t i = 0;
    char *tmp = NULL;

    if (!can_replace_variables(str, var_call, var_replace))
        return (true);;
    for (; (*str)[i]; i += 1) {
        if (my_strncmp(&(*str)[i], var_call, size_call))
            continue;
        tmp = set_new_var(*str, i, size_call, size_replace);
        if (!tmp)
            return (false);
        my_strncat(tmp, (*str), i);
        my_strcat(tmp, var_replace);
        my_strcat(tmp, &(*str)[i + size_call]);
        reset_pointers(str, &tmp);
        i = 0;
    }
    return (true);
}