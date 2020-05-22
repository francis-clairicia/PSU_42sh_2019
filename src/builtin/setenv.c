/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** setenv.c
*/

#include "minishell.h"

static int valid_arguments(char const *variable)
{
    char alphanum[] = "Variable name must contain alphanumeric characters";
    char non_letter[] = "Variable name must begin with a letter";
    char letter = 0;

    letter = variable[0];
    if ((letter >= 'A' && letter <= 'Z') == 0
    && (letter >= 'a' && letter <= 'z') == 0) {
        print_error("setenv", non_letter);
        return (0);
    }
    if (!my_str_isalphanum(variable)) {
        print_error("setenv", alphanum);
        return (0);
    }
    return (1);
}

static int add_variable(shell_t *shell, char const *variable, char const *value)
{
    int i = 0;
    char **new_envp = malloc(sizeof(char *) * (my_array_len(shell->envp) + 2));

    if (new_envp == NULL)
        return (set_exit_status(shell, 1));
    if (shell->envp != NULL) {
        while (shell->envp[i] != NULL) {
            new_envp[i] = shell->envp[i];
            i += 1;
        }
    }
    new_envp[i] = create_variable(variable, value);
    new_envp[i + 1] = NULL;
    free(shell->envp);
    shell->envp = new_envp;
    return (set_exit_status(shell, 0));
}

static int modify_variable(shell_t *shell, int var_index,
    char const *variable, char const *value)
{
    char *new_var = create_variable(variable, value);

    if (!new_var)
        return (set_exit_status(shell, 1));
    free(shell->envp[var_index]);
    shell->envp[var_index] = new_var;
    return (set_exit_status(shell, 0));
}

int setenv_builtin_command(char * const *av, shell_t *shell)
{
    int ac = my_array_len(av);
    int var_index = 0;

    if (ac < 2)
        return (print_env(shell));
    else if (ac > 3) {
        print_error("setenv", "Too many arguments");
        return (set_exit_status(shell, 1));
    }
    if (shell == NULL || !valid_arguments(av[1]))
        return (set_exit_status(shell, 1));
    var_index = find_var_env(shell->envp, av[1]);
    if (var_index < 0)
        return (add_variable(shell, av[1], av[2]));
    return (modify_variable(shell, var_index, av[1], av[2]));
}