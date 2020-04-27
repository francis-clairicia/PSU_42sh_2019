/*
** EPITECH PROJECT, 2019
** My_Lib_C
** File description:
** my_array_len.c
*/

#include <stddef.h>

int my_array_len(char * const *array)
{
    int i = 0;

    if (array == NULL)
        return (0);
    while (array[i] != NULL)
        i += 1;
    return (i);
}