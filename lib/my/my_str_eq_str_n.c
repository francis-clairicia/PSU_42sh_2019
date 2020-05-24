/*
** EPITECH PROJECT, 2019
** libmy
** File description:
** compares characters inside of two strings
*/

#include <stdbool.h>
#include "my.h"

bool my_str_eq_str_n(const char *s1, const char *s2, const size_t n)
{
    register size_t index = 0;
    ssize_t len_first = my_strlen(s1);
    ssize_t len_second = my_strlen(s2);

    if (n == 0)
        return (true);
    if (len_first == -1)
        return (len_second == -1) ? true : false;
    for (; s1[index] && s2[index] && index < n; index += 1) {
        if (s1[index] != s2[index])
            break;
    }
    if (index == n)
        return (true);
    return (s1[index] == s2[index]) ? true : false;
}
