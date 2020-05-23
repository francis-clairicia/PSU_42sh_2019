/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** mysh_shell.h
*/

#ifndef MYSH_SHELL_H_
#define MYSH_SHELL_H_

#include "mysh_parsing.h"
#include "mylist.h"

typedef struct process
{
    pid_t pid;
    char *cmd;
} process_t;

process_t *init_process_struct(pid_t pid, cmd_list_t *cmd_list);
void destroy_process_struct(process_t *process);

// Alias Struct
typedef struct alias_s {
    char *alias;
    char **cmd;
    struct alias_s *next;
} alias_t;

// end -> Alias Struct

typedef struct shell
{
    char **envp;
    int exit_status;
    list_t process;
    alias_t *alias_list;
} shell_t;

shell_t *init_shell_struct(char * const *envp);
void destroy_shell_struct(shell_t *shell);

static inline int set_exit_status(shell_t *shell, unsigned char exit_status)
{
    if (!shell)
        return (-1);
    shell->exit_status = exit_status;
    return ((shell->exit_status == 0) ? 0 : -1);
}

void check_background_process(shell_t *shell);

#endif