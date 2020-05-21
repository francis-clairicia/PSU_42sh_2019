/*
** EPITECH PROJECT, 2020
** unalias.c
** File description:
** unalias built-in command
*/

#include "minishell.h"
#include <stdio.h>

int unalias_builtin_command(char * const *av, shell_t *shell)
{
    int ac = my_array_len(av);

    if (ac == 1)
        print_error("unalias", "Too few arguments.");
    if (ac >= 2)
        printf("delete alias arg\n");
}