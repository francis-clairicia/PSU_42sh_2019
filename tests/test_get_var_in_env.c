/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_add_new_env_var.c
*/

#include <criterion/criterion.h>
#include "mysh_env.h"

Test(get_var_in_env_list, find_a_newly_added_var)
{
    env_list_t *list = NULL;
    env_list_t *ptr = NULL;

    add_new_env_var(&list, "TEST", "1");
    cr_expect(list);
    ptr = get_var_in_env_list(list, "TEST");
    cr_expect(ptr);
    cr_expect_eq(list, ptr);
    free_env_list(list);
}

Test(get_var_in_env_list, cant_find_a_var)
{
    env_list_t *list = NULL;
    env_list_t *ptr = NULL;

    add_new_env_var(&list, "PATH", "/home/");
    cr_expect(list);
    ptr = get_var_in_env_list(list, "TEST");
    cr_expect_eq(ptr, NULL);
    free_env_list(list);
}
