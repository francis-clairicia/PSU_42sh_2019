/*
** EPITECH PROJECT, 2020
** alias.c
** File description:
** alias built-in command
*/

#include "minishell.h"
#include <stdio.h>

int alias_builtin_command(char * const *av, shell_t *shell)
{
    int ac = my_array_len(av);

    if (ac == 1)
        printf("print alias list\n");
    if (ac == 2)
        printf("print cmd of %s\n", av[1]);
    if (ac >= 3)
        printf("add alias %s for all the arg\n", av[1]);
}