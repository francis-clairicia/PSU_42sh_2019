/*
** EPITECH PROJECT, 2019
** Libmy
** File description:
** Concats two strings.
*/

#include <stdlib.h>
#include "my.h"

static char *compute_concat(const char *restrict first,
                            const char *restrict second,
                            const int len_fir,
                            const int len_sec)
{
    char *result = NULL;

    result = malloc(sizeof(char) * (len_fir + len_sec + 1));
    if (!result)
        return (NULL);
    my_strcpy(result, first);
    my_strcpy(&result[my_strlen(result)], second);
    return (result);
}

char *my_strcat_malloc(char *restrict first, char *restrict second,
                const bool free_first, const bool free_second)
{
    int len_fir = my_strlen(first);
    int len_sec = my_strlen(second);
    char *result = NULL;

    if (len_fir <= 0 || len_sec <= 0)
        result = (len_fir <= 0) ? my_strdup(second) : my_strdup(first);
    else
        result = compute_concat(first, second, len_fir, len_sec);
    if (first && free_first)
        free(first);
    if (second && free_second)
        free(second);
    return (result);
}