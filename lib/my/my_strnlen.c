/*
** EPITECH PROJECT, 2019
** PSU_minishell_2019
** File description:
** gets a string len with a n factor
*/

#include <unistd.h>

ssize_t my_strnlen(const char *str, const ssize_t n)
{
    ssize_t i = -1;

    if (str)
        while (str[++i] && i < n);
    return (i);
}