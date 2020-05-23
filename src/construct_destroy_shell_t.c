/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** shell.c
*/

#include <stdlib.h>
#include "minishell.h"

static void set_default_path(shell_t *shell, char * const *envp)
{
    int index = find_var_env(envp, "PATH");
    char  *default_path[] = {
        "/usr/bin",
        "/bin",
        NULL
    };

    if (index >= 0)
        shell->path = my_str_to_word_array(get_var_value(envp, index), ":");
    else
        shell->path = my_array_dup(default_path);
}

shell_t *init_shell_struct(char * const *envp)
{
    shell_t *shell = malloc(sizeof(*shell));

    if (!shell)
        return (shell);
    my_memset(shell, 0, sizeof(*shell));
    shell->envp = my_array_dup(envp);
    shell->exit_status = 0;
    shell->history = my_list();
    set_default_path(shell, envp);
    return (shell);
}

void destroy_shell_struct(shell_t *shell)
{
    if (!shell)
        return;
    my_free_array(shell->envp);
    my_free_array(shell->path);
    my_free_list(&(shell->process), &destroy_process_struct);
    my_free_list(&(shell->history), &free);
    free(shell);
}