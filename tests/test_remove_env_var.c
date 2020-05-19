/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_add_new_env_var.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "mysh_env.h"

Test(remove_env_var, remove_the_only_node_from_list)
{
    env_list_t *list = NULL;

    cr_redirect_stdout();
    add_new_env_var(&list, "SHLVL", "2");
    cr_expect_eq(remove_env_var(&list, "SHLVL"), true);
    cr_expect_eq(list, NULL);
    free_env_list(list);
}

Test(remove_env_var, remove_unexistant_variable_from_not_empty_list)
{
    env_list_t *list = NULL;

    cr_redirect_stdout();
    add_new_env_var(&list, "SHLVL", "2");
    cr_expect_eq(remove_env_var(&list, "TEST"), false);
    free_env_list(list);
}

Test(remove_env_var, remove_unexistant_variable_from_empty_list)
{
    env_list_t *list = NULL;

    cr_redirect_stdout();
    cr_expect_eq(remove_env_var(&list, "TEST"), false);
    cr_expect_eq(list, NULL);
    free_env_list(list);
}
