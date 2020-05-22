/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** test_error.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(print_error, print_in_stderr)
{
    cr_redirect_stderr();
    print_error("p", "n");
    cr_expect_stderr_eq_str("p: n.\n");
}

Test(print_signal, print_caught_signal)
{
    cr_redirect_stderr();
    print_signal(SIGSEGV, 1, true);
    print_signal(SIGFPE, 0, false);
    cr_expect_stderr_eq_str(
        "Segmentation fault (core dumped)\n"
        "Floating exception"
    );
}

Test(error_exec, returns_the_correct_strerror)
{
    char error_file[] = "No such file or directory";
    char error_format[] = "Exec format error. Wrong Architecture";

    cr_assert_str_eq(error_exec(ENOENT), error_file);
    cr_assert_str_eq(error_exec(ENOEXEC), error_format);
}