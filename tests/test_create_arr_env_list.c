/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_create_env_list_arr.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my.h"
#include "mysh_env.h"

Test(create_array_from_env_list, basic_env_array_conception)
{
    env_list_t *list = NULL;
    char **result = NULL;
    const char *expected[] = {"SHLVL=1",
                        "HOME=/home/",
                        "PATH=/usr/bin/lib",
                        NULL};

    cr_redirect_stdout();
    list = create_env_list_from_array(expected);
    result = create_array_from_env_list(list);
    free_env_list(list);
    cr_expect(my_arrcmp((char **)expected, result));
    my_free_array((void *)result);
}

Test(create_array_from_env_list, null_sent)
{
    char **result = NULL;

    result = create_array_from_env_list(NULL);
    cr_expect_eq(result, NULL);
    my_free_array((void *)result);
}
