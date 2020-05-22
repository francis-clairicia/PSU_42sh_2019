/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** get_path_from_str.c
*/

#include "my.h"

char *get_matching_from_str(const char *str)
{
    register ssize_t index = 0;

    if (!str)
        return (NULL);
    index = my_strlen(str) - 1;
    for (; index >= 0 && str[index] != '/'; index -= 1);
    return (my_strndup(str, (int)(index + 1)));
}

char *get_path_from_str(const char *str)
{
    register ssize_t index = 0;

    if (!my_strchr((char *)str, '/'))
        return (NULL);
    index = my_strlen(str) - 1;
    for (; index > 0 && str[index] != '/'; index -= 1);
    return (my_strndup(str, (int)(index + 1)));
}
