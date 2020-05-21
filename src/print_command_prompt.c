/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** print_command_prompt.c
*/

#include "minishell.h"

static bool print_user(char * const *envp)
{
    char *user = get_var_env(envp, "USER");
    char *hostname = get_var_env(envp, "HOSTNAME");
    int dot = my_strchr_index(hostname, '.');

    if (user == NULL && hostname == NULL)
        return (false);
    my_putstr(user);
    if (!hostname)
        return (true);
    my_putchar('@');
    if (dot < 0)
        my_putstr(hostname);
    else
        write(1, hostname, dot);
    return (true);
}

static void print_current_directory(char const *cwd, char * const *envp)
{
    char *home_path = get_var_env(envp, "HOME");
    int len_home_path = my_strlen(home_path);

    if (cwd == NULL)
        return;
    if (my_strncmp(cwd, home_path, len_home_path) == 0) {
        my_putstr("~");
        cwd = &cwd[len_home_path];
        if (my_strchr_index(cwd, '/') < 0)
            return;
        cwd = &cwd[my_strchr_index(cwd, '/') + 1];
        if (my_strlen(cwd) == 0)
            return;
        my_putstr("/");
    }
    my_putstr(cwd);
}

void print_command_prompt(char const *cwd, char * const *envp)
{
    my_putstr("[");
    if (print_user(envp))
        my_putchar(' ');
    print_current_directory(cwd, envp);
    my_putstr("]$ ");
}