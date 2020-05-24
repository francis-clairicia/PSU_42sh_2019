/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** mysh_shell.h
*/

#ifndef MYSH_SHELL_H_
#define MYSH_SHELL_H_

#include "mylist.h"
#include "mysh_variables.h"
#include "mysh_aliases.h"

typedef struct shell
{
    char **envp;
    char **path;
    int exit_status;
    list_t process;
    list_t history;
    var_list_t *var_list;
    alias_t *alias_list;
} shell_t;

#define FIND_ENV(shell) ((shell) ? shell->envp : NULL)

shell_t *init_shell_struct(char * const *envp);
void destroy_shell_struct(shell_t *shell);

typedef void (*set_default_var_t)(shell_t *);
void set_default_path(shell_t *shell);

static inline int set_exit_status(shell_t *shell, unsigned char exit_status)
{
    if (!shell)
        return (-1);
    shell->exit_status = exit_status;
    return ((shell->exit_status == 0) ? 0 : -1);
}

////////////////////////
#include "mysh_parsing.h"
////////////////////////

typedef struct process
{
    pid_t pid;
    char *cmd;
} process_t;

process_t *init_process_struct(pid_t pid, cmd_list_t *cmd_list);
void destroy_process_struct(process_t *process);

void check_background_process(shell_t *shell);

#endif