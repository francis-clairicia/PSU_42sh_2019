/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_get_var_value.c
*/

#include <criterion/criterion.h>
#include "minishell.h"

Test(get_var_value, get_value_of_variable_environment)
{
    char *custom_env[] = {"USER=user", "HOST=", "NO_VALUE", NULL};

    cr_expect_str_eq(get_var_value(custom_env, 0), "user");
    cr_expect_str_eq(get_var_value(custom_env, 1), "");
    cr_expect_null(get_var_value(custom_env, -1));
    cr_expect_null(get_var_value(NULL, 0));
    cr_expect_null(get_var_value(custom_env, 2));
}