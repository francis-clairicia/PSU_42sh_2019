/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** test_find_completion
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "auto_completion.h"

Test(find_completion, arg_error)
{
    auto_completion_t *list = NULL;

    cr_expect(!find_completion(NULL, NULL));
    cr_expect(!find_completion("patate", NULL));
    cr_expect(!find_completion(NULL, &list));
}

Test(find_completion, success_1)
{
    auto_completion_t *list = NULL;

    if (!find_completion("./tests/test_completion/pata", &list))
        cr_assert(0);
    cr_assert(list && !strcmp(list->completion, "te"));
}

Test(find_completion, success_2)
{
    auto_completion_t *list = NULL;

    if (!find_completion("./tests/test_completion/", &list))
        cr_assert(0);
    cr_assert(list && (!strcmp(list->completion, "patate") ||
    !strcmp(DCLL_NEXT_C(list, auto_completion_t *)->completion, "patate")));
}