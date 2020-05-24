/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_parse_input.c
*/

#include <criterion/criterion.h>
#include "mysh_parsing.h"

Test(parse_input, null_sent)
{
    parse_list_t *list = NULL;

    list = parse_input(NULL, NULL, NULL);
    cr_expect_eq(list, NULL);
    free_parse_list(list);
}

Test(parse_input, easy_input)
{
    shell_t *shell = init_shell_struct(NULL);
    parse_list_t *list = NULL;
    const char input[] = "ls -a";
    error_parse_t error = NONE;

    list = parse_input(input, shell, &error);
    cr_expect_not_null(list);
    if (list) {
        cr_expect_eq(my_strcmp(list->cmd_list->args->arg, "ls"), 0);
        cr_expect_eq(list->cmd_list->args->next->arg,
                    list->cmd_list->args->prev->arg);
        cr_expect_eq(my_strcmp(list->cmd_list->args->prev->arg, "-a"), 0);
        free_parse_list(list);
    }
    destroy_shell_struct(shell);
    cr_assert_eq(error, NONE);
}

Test(parse_input, hard_input)
{
    parse_list_t *list = NULL;
    const char input[] = "ls \"-a\"|\t cat '-e' > 'txt'\"a\"";
    shell_t *shell = init_shell_struct(NULL);
    error_parse_t error = NONE;

    list = parse_input(input, shell, &error);
    cr_expect_not_null(list);
    if (list) {
        cr_expect_eq(my_strcmp(list->cmd_list->args->arg, "ls"), 0);
        cr_expect_eq(my_strcmp(list->cmd_list->args->prev->arg, "-a"), 0);
        cr_expect_eq(list->cmd_list->redir_output_type, PIPE);
        cr_expect_eq(my_strcmp(list->cmd_list->next->args->arg, "cat"), 0);
        cr_expect_eq(my_strcmp(list->cmd_list->next->args->prev->arg, "-e"), 0);
        cr_expect_eq(list->cmd_list->next->redir_output_type, REDIR_IN_FILE);
        cr_expect_str_eq(list->cmd_list->next->redir_output, "txta");
        free_parse_list(list);
    }
    destroy_shell_struct(shell);
    cr_assert_eq(error, NONE);
}
