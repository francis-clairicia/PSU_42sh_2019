/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** shell.c
*/

#include <stdlib.h>
#include "minishell.h"

static const set_default_var_t set_default_var[] = {
    set_default_path,
    NULL
};

shell_t *init_shell_struct(char * const *envp)
{
    shell_t *shell = malloc(sizeof(*shell));

    if (!shell)
        return (shell);
    my_memset(shell, 0, sizeof(*shell));
    shell->envp = my_array_dup(envp);
    shell->exit_status = 0;
    for (int i = 0; set_default_var[i]; i += 1)
        set_default_var[i](shell);
    return (shell);
}