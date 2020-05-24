/*
** EPITECH PROJECT, 2019
** Libmy
** File description:
** Concats two strings.
*/

#include <stdlib.h>
#include "my.h"

char *my_strncat_malloc(const char *first, const char *second, const ssize_t n)
{
    char *result = NULL;
    ssize_t len_first = my_strlen(first);
    ssize_t len_second = my_strnlen(second, n);
    ssize_t len_result = len_first + len_second;

    if (len_result < 0)
        return (NULL);
    result = malloc(sizeof(char) * (len_result + 1));
    if (!result)
        return (NULL);
    my_strcpy(result, first);
    my_strncpy(&result[my_strlen(result)], second, n);
    return (result);
}