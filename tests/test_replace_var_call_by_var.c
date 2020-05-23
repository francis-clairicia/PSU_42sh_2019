/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_replace_var_call_by_var.c
*/

#include <criterion/criterion.h>
#include "mysh_parsing.h"

Test(replace_var_call_by_var, simple_replace)
{
    char *str = my_strdup("ls $PATH");

    cr_expect(replace_var_call_by_var(&str, "$PATH", "/home/"));
    cr_expect_str_eq(str, "ls /home/");
    if (str)
        free(str);
}

Test(replace_var_call_by_var, several_replaces)
{
    char *str = my_strdup("ls $PATH $PATH");

    cr_expect(replace_var_call_by_var(&str, "$PATH", "/home/"));
    cr_expect_str_eq(str, "ls /home/ /home/");
    if (str)
        free(str);
}

Test(replace_var_call_by_var, replace_noting)
{
    char *str = my_strdup("ls $PATH $PATH");

    cr_expect(replace_var_call_by_var(&str, NULL, NULL));
    cr_expect_str_eq(str, "ls $PATH $PATH");
    if (str)
        free(str);
}