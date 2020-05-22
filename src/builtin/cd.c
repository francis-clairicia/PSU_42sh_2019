/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** cd.c
*/

#include "minishell.h"

static int go_to_default_home_path(shell_t *shell)
{
    char *home_path = get_var_env(shell->envp, "HOME");

    if (home_path == NULL)
        return (0);
    if (chdir(home_path) < 0) {
        print_error(home_path, strerror(errno));
        return (0);
    }
    return (1);
}

static int go_to_old_directory(shell_t *shell)
{
    char *old_pwd = get_var_env(shell->envp, "OLDPWD");

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

static int change_directory(char const *arg, shell_t *shell)
{
    if (my_strcmp(arg, "-") == 0)
        return (go_to_old_directory(shell));
    if (chdir(arg) < 0) {
        print_error(arg, strerror(errno));
        shell->exit_status = 1;
        return (0);
    }
    return (1);
}

static int set_oldpwd_var(char const *old_pwd, shell_t *shell)
{
    if (set_var_to_env("OLDPWD", old_pwd, shell) == -1)
        return (-1);
    if (set_var_to_env("PWD", getcwd(NULL, 0), shell))
        return (-1);
    return (set_exit_status(shell, 0));
}

int cd_builtin_command(char * const *av, shell_t *shell)
{
    int ac = my_array_len(av);
    char old_pwd[4097];

    if (ac > 2) {
        print_error("cd", "Too many arguments");
        return (set_exit_status(shell, 1));
    }
    if (!shell || !(shell->envp) || getcwd(old_pwd, 4097) == NULL)
        return (-1);
    if (ac == 1 && !go_to_default_home_path(shell))
        return (set_exit_status(shell, 1));
    if (ac > 1 && !change_directory(av[1], shell))
        return (set_exit_status(shell, 1));
    return (set_oldpwd_var(old_pwd, shell));
}