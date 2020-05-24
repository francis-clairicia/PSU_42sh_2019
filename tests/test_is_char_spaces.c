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

    while (SPACES[i]) {
        cr_assert(IS_CHAR_SPACES(SPACES[i]));
        i += 1;
    }
}

Test(is_char_spaces, given_others)
{
    cr_assert_eq(IS_CHAR_SPACES('c'), false);
}
