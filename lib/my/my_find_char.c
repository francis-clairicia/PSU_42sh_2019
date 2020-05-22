/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** my_find_char
*/

#include <stdlib.h>

int my_find_char(const char *str, char to_find)
{
    int index = 0;

    if (!str)
        return (-1);
    while (str[index]) {
        if (!(str[index] ^ to_find))
            return (index);
        index += 1;
    }
    return (-1);
}

int my_find_char_tempate(const char *str, const int *template, char to_find)
{
    int index = 0;

    if (!str || !template)
        return (-1);
    while (str[index] && template[index]) {
        if (!(str[index] ^ to_find))
            return (template[index]);
        index += 1;
    }
    return (-1);
}