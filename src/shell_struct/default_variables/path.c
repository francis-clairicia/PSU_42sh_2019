/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** path.c
*/

#include "minishell.h"

static void set_path(shell_t *shell, char const *path_list)
{
    char *path = my_strdup(path_list);
    int index = 0;

    while ((index = my_strchr_index(path, ':')) >= 0)
        path[index] = ' ';
    add_var_to_var_list(&shell->var_list, "path", path);
    free(path);
    shell->path = my_str_to_word_array(path_list, ":");
}

void set_default_path(shell_t *shell)
{
    int index = find_var_env(shell->envp, "PATH");

    if (index >= 0)
        set_path(shell, get_var_value(shell->envp, index));
    else
        set_path(shell, "/usr/bin:/bin");
}