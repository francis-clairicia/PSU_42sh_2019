/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** exit.c
*/

#include "my.h"
#include "minishell.h"

int exit_builtin_command(char * const *av, shell_t *shell)
{
    int ac = my_array_len(av);

     if (ac >= 2) {
        if (ac > 2 || !my_str_isnum(av[1])) {
            print_error("exit", "Expression Syntax");
            return (-1);
        }
        shell->exit_status = (unsigned char)my_absolute_getnbr(av[1]);
    }
    my_putstr("exit\n");
    return (1);
}