/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_create_env_list_arr.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "mysh_env.h"

Test(create_env_list_from_array, basic_env_list_conception)
{
    env_list_t *list = NULL;
    const char *envg[] = {"SHLVL=1",
                        "HOME=/home/",
                        "PATH=/usr/bin/lib",
                        NULL};

    cr_redirect_stdout();
    list = create_env_list_from_array(envg);
    show_env(list);
    cr_expect_stdout_eq_str("SHLVL=1\n"
                            "HOME=/home/\n"
                            "PATH=/usr/bin/lib\n");
    free_env_list(list);
}
