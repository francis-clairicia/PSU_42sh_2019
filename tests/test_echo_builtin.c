/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_echo_builtin.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(echo_builtin_command, print_words_separated_by_spaces_ends_with_newline)
{
    shell_t *shell = init_shell_struct(NULL);

    cr_redirect_stdout();
    cr_expect_eq(eval_exec_cmd("echo \"Hello It's Me\"", shell), 0);
    cr_expect_stdout_eq_str("Hello It's Me\n");
    destroy_shell_struct(shell);
}

Test(echo_builtin_command, handle_n_flag_no_print_new_line)
{
    shell_t *shell = init_shell_struct(NULL);

    cr_redirect_stdout();
    cr_expect_eq(eval_exec_cmd("echo -n \"Hello It's Me\"", shell), 0);
    cr_expect_stdout_eq_str("Hello It's Me");
    destroy_shell_struct(shell);
}