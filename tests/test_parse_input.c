/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_parse_input.c
*/

#include <string.h>
#include <criterion/criterion.h>
#include "mysh_parsing.h"

Test(parse_input, null_sent)
{
    parsed_input_list_t *list = NULL;

    list = parse_input(NULL, NULL);
    cr_expect_eq(list, NULL);
}

Test(parse_input, easy_input)
{
    parsed_input_list_t *list = NULL;
    const char input[] = "ls -a";
    error_parse_t error = NONE;

    list = parse_input(input, &error);
    if (!list)
        cr_assert(0);
    cr_expect(!strcmp(list->cmd_list->args->arg, "ls"));
    cr_expect_eq(DCLL_NEXT_C(list->cmd_list->args, arguments_t *)->arg,
                DCLL_PREV_C(list->cmd_list->args, arguments_t *)->arg);
    cr_expect(!strcmp(
        DCLL_PREV_C(list->cmd_list->args, arguments_t *)->arg, "-a"));
    cr_assert_eq(error, NONE);
}

Test(parse_input, hard_input)
{
    parsed_input_list_t *list = NULL;
    const char input[] = "ls \"-a\"|\t cat '-e' > 'txt'\"a\"";
    error_parse_t error = NONE;

    list = parse_input(input, &error);
    if (!list)
        cr_assert(0);
    cr_expect(!strcmp(list->cmd_list->args->arg, "ls"));
    cr_expect(!strcmp(DCLL_PREV_C(list->cmd_list->args, arguments_t *)->arg,
                                                                        "-a"));
    cr_expect(list->cmd_list->redir_type == PIPE);
    cr_expect(!strcmp(DCLL_NEXT_C(list->cmd_list, cmd_list_t *)->args->arg,
                                                                        "cat"));
    cr_expect(!strcmp(DCLL_PREV_C(DCLL_NEXT_C
            (list->cmd_list, cmd_list_t *)->args, arguments_t *)->arg, "-e"));
    cr_expect(
        DCLL_NEXT_C(list->cmd_list, cmd_list_t *)->redir_type == REDIR_IN_FILE);
    cr_expect_str_eq(
        DCLL_NEXT_C(list->cmd_list, cmd_list_t *)->redir_name, "txta");
    cr_assert(error == NONE);
}