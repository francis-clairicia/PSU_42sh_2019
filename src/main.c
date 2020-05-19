/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** main.c
*/

#include "my.h"

int mysh(void);

static int print_help(void)
{
    my_putstr("USAGE\n");
    my_putstr("\t./mysh\n\n");
    my_putstr("DESCRIPTION\n");
    my_putstr("\tA C-coded minishell\n");
    return (0);
}

int main(int ac, char **av)
{
    if (ac > 1 && my_strcmp(av[1], "-h") == 0)
        return (print_help());
    return (mysh());
}