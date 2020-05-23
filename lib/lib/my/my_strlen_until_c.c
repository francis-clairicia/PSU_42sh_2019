/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** gets a string len until meeting a certain char
*/

#include "my.h"

ssize_t my_strlen_until_c(const char *str, const char c)
{
    ssize_t index = -1;

    if (str)
        while (str[++index] && c != str[index]);
    return (index);
}