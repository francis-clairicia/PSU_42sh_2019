/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** destroy_shell.c
*/

#include "mysh_shell.h"

void destroy_shell_struct(shell_t *shell)
{
    if (!shell)
        return;
    my_free_array(shell->envp);
    my_free_array(shell->path);
    free_var_list(shell->var_list);
    my_free_list(&(shell->process), &destroy_process_struct);
    my_free_list(&(shell->history), &free);
    destroy_every_alias(&(shell->alias_list));
    free(shell);
}