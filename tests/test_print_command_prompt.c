/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** test_print_command_prompt.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(print_command_prompt, print_user_and_cwd)
{
    char *envp[] = {
        "USER=user",
        "HOSTNAME=localhost.localdomain",
        NULL
    };

    cr_redirect_stdout();
    print_command_prompt("/usr/bin", envp);
    cr_expect_stdout_eq_str("[user@localhost /usr/bin]$ ");
}

Test(print_command_prompt, print_tilde_for_the_home_path)
{
    char *envp[] = {
        "USER=user",
        "HOSTNAME=localhost",
        "HOME=/home/user",
        NULL
    };

    cr_redirect_stdout();
    print_command_prompt("/home/user", envp);
    my_putchar('\n');
    print_command_prompt("/home/user/Downloads", envp);
    cr_expect_stdout_eq_str("[user@localhost ~]$ \n"
        "[user@localhost ~/Downloads]$ ");
}

Test(print_command_prompt, handle_null_cwd_value)
{
    char *envp[] = {
        "USER=user",
        "HOSTNAME=localhost.localdomain",
        NULL
    };

    cr_redirect_stdout();
    print_command_prompt(NULL, envp);
    cr_expect_stdout_eq_str("[user@localhost ]$ ");
}

Test(print_command_prompt, handle_null_env_value)
{
    cr_redirect_stdout();
    print_command_prompt("/usr/bin", NULL);
    cr_expect_stdout_eq_str("[ /usr/bin]$ ");
}