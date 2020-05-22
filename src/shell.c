/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** shell.c
*/

#include <stdlib.h>
#include "minishell.h"

static void set_default_path(shell_t *shell)
{
    char const default_path[] = {
        "/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin"
    };

    set_var_to_env("PATH", default_path, shell);
}

shell_t *init_shell_struct(char * const *envp)
{
    shell_t *shell = malloc(sizeof(*shell));

    if (!shell)
        return (shell);
    my_memset(shell, 0, sizeof(*shell));
    shell->envp = my_array_dup(envp);
    shell->exit_status = 0;
    if (my_array_len(shell->envp) == 0)
        set_default_path(shell);
    return (shell);
}

void destroy_shell_struct(shell_t *shell)
{
    if (!shell)
        return;
    my_free_array(shell->envp);
    my_free_list(&(shell->process), &destroy_process_struct);
    free(shell);
}