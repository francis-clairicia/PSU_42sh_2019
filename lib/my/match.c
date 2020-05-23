/*
** EPITECH PROJECT, 2019
** Match
** File description:
** checks if a string containing wild cards matches with another one.
*/

#include <stdbool.h>
#include <unistd.h>
#include "my_wildcards.h"

static bool check_for_null_except(const char *first, const char *second)
{
    register size_t i = 0;

    if (first == second)
        return (true);
    if (first) {
        for (; first[i] && first[i] == GLOBAL_WC; i += 1);
        return (i > 0) ? (first[i] ? false : true) : false;
    }
    return (false);
}

static ssize_t my_strlen(const char *str)
{
    ssize_t i = -1;

    if (str)
        while (str[++i]);
    return (i);
}

static bool get_second_anchor(const char anchor, char **tmp)
{
    ssize_t size = my_strlen(*tmp);

    if (size < 0)
        return (0);
    *tmp += size;
    for (; (**tmp) != anchor && size > 0; *tmp -= 1)
        size -= 1;
    return ((**tmp) == anchor);
}

bool match(const char *first, const char *second)
{
    char *anchor = (char *)first;
    char *tmp = (char *)second;

    if (!first || !second)
        return (check_for_null_except(first, second));
    if ((*first) == (*second))
        return (!(*first) && !(*second)) ? true : match(first + 1, second + 1);
    if ((*anchor) == SOLO_WC)
        return (match(first + 1, second + 1));
    if ((*anchor) == GLOBAL_WC) {
        while ((*anchor == GLOBAL_WC || *anchor == SOLO_WC) && *anchor)
            anchor += 1;
        if (!get_second_anchor(*anchor, &tmp))
            return (false);
        return (match(anchor, tmp));
    }
    return (false);
}
