/*
** EPITECH PROJECT, 2019
** Libmy
** File description:
** Loops while the character on str is in list. Increases i.
*/

#include "my.h"

bool my_loop_in_str_while_list_c(const char *str, const char list[], size_t *i)
{
    size_t tmp = *i;
    bool ret_val = false;

    if (!str)
        return (false);
    if (str[tmp] && my_is_char_in_str(list, str[tmp]))
        ret_val = true;
    for (; str[tmp] && my_is_char_in_str(list, str[tmp]); tmp += 1)
        ret_val = true;
    *i = tmp;
    return (ret_val);
}