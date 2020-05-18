/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_add_new_env_var.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "mysh_env.h"

Test(show_env, show_basic_env)
{
    env_list_t *list = NULL;

    cr_redirect_stdout();
    add_new_env_var(&list, "SHLVL", "1");
    add_new_env_var(&list, "PATH", "/home/");
    add_new_env_var(&list, "HOME", "/home/gbogard/");
    show_env(list);
    cr_expect_stdout_eq_str("SHLVL=1\n"
                            "PATH=/home/\n"
                            "HOME=/home/gbogard/\n");
    free_env_list(list);
}

Test(show_env, null_sent)
{
    show_env(NULL);
}
