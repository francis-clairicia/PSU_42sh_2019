/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** cd.c
*/

#include "minishell.h"

static int go_to_default_home_path(char * const *envp)
{
    char *home_path = get_var_value(envp, find_var_env(envp, "HOME"));

    if (home_path == NULL)
        return (0);
    if (chdir(home_path) < 0) {
        print_error(home_path, strerror(errno));
        return (0);
    }
    return (1);
}

static int go_to_old_directory(char * const *envp)
{
    char *old_pwd = get_var_value(envp, find_var_env(envp, "OLDPWD"));

    if (old_pwd == NULL) {
        print_error("", strerror(ENOENT));
        return (0);
    }
    if (chdir(old_pwd) < 0) {
        print_error(old_pwd, strerror(errno));
        return (0);
    }
    return (1);
}

static int change_directory(char const *arg, char * const *envp)
{
    if (my_strcmp(arg, "-") == 0)
        return (go_to_old_directory(envp));
    if (chdir(arg) < 0) {
        print_error(arg, strerror(errno));
        return (0);
    }
    return (1);
}

int cd_builtin_command(char * const *av, char ***envp)
{
    int ac = my_array_len(av);
    char actual_dir[4097];
    char *set_old_pwd[] = {"setenv", "OLDPWD", actual_dir, NULL};
    char *set_new_pwd[] = {"setenv", "PWD", actual_dir, NULL};

    if (ac > 2) {
        print_error("cd", "Too many arguments");
        return (-1);
    }
    if (envp == NULL || getcwd(actual_dir, 4097) == NULL)
        return (-1);
    if (ac == 1 && !go_to_default_home_path(*envp))
        return (-1);
    if (ac > 1 && !change_directory(av[1], *envp))
        return (-1);
    setenv_builtin_command(set_old_pwd, envp);
    getcwd(actual_dir, 4097);
    setenv_builtin_command(set_new_pwd, envp);
    return (0);
}