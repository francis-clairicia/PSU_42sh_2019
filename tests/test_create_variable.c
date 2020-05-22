/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_create_variable.c
*/

#include <criterion/criterion.h>
#include "minishell.h"

Test(create_variable, create_a_new_variable_for_the_env)
{
    char *variable = create_variable("USER", "2");

    cr_expect_str_eq(variable, "USER=2");
    free(variable);
}

Test(create_variable, cant_create_if_var_is_null)
{
    char *variable = create_variable(NULL, "Hello");

    cr_expect_null(variable);
}