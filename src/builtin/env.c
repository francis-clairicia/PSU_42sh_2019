/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** env.c
*/

#include "minishell.h"

int env_builtin_command(char * const *av, shell_t *shell)
{
    int ac = my_array_len(av);
    int i = 0;

    if (ac > 1) {
        print_error("env", "Too many arguments");
        return (-1);
    }
    if (shell == NULL || shell->envp == NULL)
        return (-1);
    while (shell->envp[i] != NULL) {
        my_printf("%s\n", shell->envp[i]);
        i += 1;
    }
    return (0);
}