/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** my_get_bitshift.c
*/

#include <stddef.h>

size_t my_get_bitshift(const void *variable)
{
    size_t nb = 0;
    char *tmp = (void *)variable;

    for (; (*tmp); (*tmp) >>= 1)
        nb += 1;
    return (nb);
}
