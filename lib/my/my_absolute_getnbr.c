/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** my_absolute_getnbr.c
*/

#include "my.h"

ssize_t my_absolute_getnbr(const char *str)
{
    register size_t index = 0;
    ssize_t nb = 0;
    int neg = 1;

    if (!str)
        return (-1);
    if (!my_str_isnum(str))
        return (-1);
    if (str[0] == '-') {
        neg = -1;
        index += 1;
    }
    for (; str[index]; index += 1) {
        if (index > 0)
            nb *= 10;
        nb += str[index] - 48;
    }
    return (nb * neg);
}
