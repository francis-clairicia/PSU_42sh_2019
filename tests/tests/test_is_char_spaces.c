/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_is_char_spaces.c
*/

#include <criterion/criterion.h>
#include "mysh_parsing.h"

Test(is_char_spaces, given_spaces)
{
    register size_t i = 0;

    while (spaces[i]) {
        cr_assert(is_char_spaces(spaces[i]));
        i += 1;
    }
}

Test(is_char_spaces, given_others)
{
    cr_assert_eq(is_char_spaces('c'), false);
}
