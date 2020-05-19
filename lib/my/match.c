/*
** EPITECH PROJECT, 2019
** Match
** File description:
** checks if a string containing wild cards matches with another one.
*/

#include <stdbool.h>
#include <stddef.h>

static bool is_only_wild_cards(const char *str)
{
    register size_t i = 0;

    if (!str)
        return (false);
    for (; str[i] && str[i] == '*'; i += 1);
    return (i > 0) ? (str[i] ? false : true) : false;
}

static bool check_for_null_except(const char *first, const char *second)
{
    if (is_only_wild_cards(first))
        return (true);
    if (first == second)
        return (true);
    return (false);
}

bool match(const char *first, const char *second)
{
    char *anchor = (char *)first;
    char *tmp = (char *)second;

    if (!first || !second)
        return (check_for_null_except(first, second));
    if (!(*first) && !(*second))
        return (true);
    if ((*first) == (*second))
        return (match((first + 1), (second + 1)));
    if ((*anchor) == '*') {
        while ((*anchor) == '*' && (*(anchor + 1)) == '*' && (*(anchor + 1)))
            anchor += 1;
        for (; (*tmp) && (*tmp) != (*(anchor + 1)); tmp += 1);
        return (match(anchor + 1, tmp));
    }
    return (false);
}
