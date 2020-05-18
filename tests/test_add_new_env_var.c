/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_add_new_env_var.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "mysh_env.h"

Test(add_new_env_var, from_null_env_add_var)
{
    env_list_t *list = NULL;

    cr_redirect_stdout();
    if (!add_new_env_var(&list, "SHLVL", "1"))
        cr_expect(0);
    else {
        show_env(list);
        cr_expect_stdout_eq_str("SHLVL=1\n");
    }
    free_env_list(list);
}

Test(add_new_env_var, from_none_null_env_add_var)
{
    env_list_t *list = NULL;

    cr_redirect_stdout();
    add_new_env_var(&list, "PATH", "/home/");
    if (!add_new_env_var(&list, "SHLVL", "1"))
        cr_expect(0);
    else {
        show_env(list);
        cr_expect_stdout_eq_str("PATH=/home/\n"
                                "SHLVL=1\n");
    }
    free_env_list(list);
}

Test(add_new_env_var, rare_sent_null_address)
{
    cr_assert_eq(add_new_env_var(NULL, "PATH", "/home/"), false);
}
