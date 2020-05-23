/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** echo.c
*/

#include "minishell.h"

int echo_builtin_command(char * const *av, shell_t *shell)
{
    int i = 1;
    bool newline = true;

    if (my_strcmp(av[1], "-n") == 0) {
        newline = false;
        i += 1;
    }
    for (; av[i]; i += 1) {
        my_putstr(av[i]);
        if (av[i + 1])
            my_putchar(' ');
    }
    if (newline)
        my_putchar('\n');
    return (set_exit_status(shell, 0));
}