/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** mysh_shell.h
*/

#ifndef MYSH_SHELL_H_
#define MYSH_SHELL_H_

typedef struct shell
{
    char **envp;
    int exit_status;
} shell_t;

shell_t *init_shell_struct(char * const *envp);
void destroy_shell_struct(shell_t *shell);

#endif