/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** my_isalpha.c
*/

#include <stdbool.h>

bool my_isalpha(const char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}