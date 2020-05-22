/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** exit.c
*/

#include "minishell.h"

int exit_builtin_command(char * const *av UNUSED, shell_t *shell UNUSED)
{
    my_putstr("exit\r\n");
    return (1);
}