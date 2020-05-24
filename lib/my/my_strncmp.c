/*
** EPITECH PROJECT, 2019
** my_strncmp.c
** File description:
** Compare the n first character of two strings
*/

#include <stddef.h>

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    if (s1 == NULL || s2 == NULL)
        return (-1);
    while ((s1[i] != '\0') && (s2[i] != '\0') && i < n) {
        if (s1[i] < s2[i])
            return (-1);
        if (s1[i] > s2[i])
            return (1);
        i += 1;
    }
    if (i == n || ((s1[i] == '\0') && (s2[i] == '\0'))) {
        return (0);
    } else if (s1[i] == '\0') {
        return (-1);
    } else {
        return (1);
    }
}
