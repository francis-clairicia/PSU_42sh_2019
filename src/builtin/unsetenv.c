/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** unsetenv.c
*/

#include "minishell.h"

static void remove_var(char **envp, int var_index)
{
    int i = var_index;

    if (var_index < 0)
        return;
    free(envp[var_index]);
    while (envp[i] != NULL) {
        envp[i] = envp[i + 1];
        i += 1;
    }
}

int unsetenv_builtin_command(char * const *av, shell_t *shell)
{
    int ac = my_array_len(av);
    int i = 1;

    if (ac < 2) {
        print_error("unsetenv", "Too few arguments");
        return (set_exit_status(shell, 1));
    }
    if (shell == NULL || shell->envp == NULL)
        return (-1);
    while (i < ac) {
        remove_var(shell->envp, find_var_env(shell->envp, av[i]));
        i += 1;
    }
    return (set_exit_status(shell, 0));
}