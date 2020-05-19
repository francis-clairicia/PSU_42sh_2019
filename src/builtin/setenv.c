/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
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

static int add_variable(char ***envp, char const *variable, char const *value)
{
    int i = 0;
    char **new_envp = malloc(sizeof(char *) * (my_array_len(*envp) + 2));

    if (new_envp == NULL)
        return (-1);
    if ((*envp) != NULL) {
        while ((*envp)[i] != NULL) {
            new_envp[i] = (*envp)[i];
            i += 1;
        }
    }
    new_envp[i] = create_variable(variable, value);
    new_envp[i + 1] = NULL;
    free(*envp);
    *envp = new_envp;
    return (0);
}

int setenv_builtin_command(char * const *av, char ***envp)
{
    int ac = my_array_len(av);
    int var_index = 0;

    if (ac < 2)
        return (env_builtin_command((char *[]){"env", NULL}, envp));
    else if (ac > 3) {
        print_error("setenv", "Too many arguments");
        return (-1);
    }
    if (envp == NULL || !valid_arguments(av[1]))
        return (-1);
    var_index = find_var_env(*envp, av[1]);
    if (var_index < 0)
        return (add_variable(envp, av[1], av[2]));
    free((*envp)[var_index]);
    (*envp)[var_index] = create_variable(av[1], av[2]);
    return (0);
}