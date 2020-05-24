/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** process.c
*/

#include "mysh_shell.h"

static char *add_redirection(char *cmd, cmd_list_t *cmd_list)
{
    if (cmd_list->redir_input_type != NONE) {
        cmd = my_strcat_malloc(cmd, " ", true, false);
        if (cmd_list->redir_input_type == READ_FROM_FILE_AS_INPUT)
            cmd = my_strcat_malloc(cmd, "< ", true, false);
        if (cmd_list->redir_input_type == READ_FROM_STDIN_AS_INPUT)
            cmd = my_strcat_malloc(cmd, "<< ", true, false);
        cmd = my_strcat_malloc(cmd, cmd_list->redir_input, true, false);
    }
    if (cmd_list->redir_output_type != NONE) {
        cmd = my_strcat_malloc(cmd, " ", true, false);
        if (cmd_list->redir_input_type == REDIR_IN_FILE)
            cmd = my_strcat_malloc(cmd, "> ", true, false);
        if (cmd_list->redir_input_type == APPEND_TO_FILE)
            cmd = my_strcat_malloc(cmd, ">> ", true, false);
        if (cmd_list->redir_input_type == PIPE)
            cmd = my_strcat_malloc(cmd, "| ", true, false);
        cmd = my_strcat_malloc(cmd, cmd_list->redir_input, true, false);
    }
    return (cmd);
}

static char *add_cmd(char *cmd, arguments_t *args)
{
    int index = 0;

    if (!args)
        return (NULL);
    for (arguments_t *arg = args; index == 0 || args != arg; index += 1) {
        cmd = my_strcat_malloc(cmd, arg->arg, true, false);
        arg = arg->next;
        if (arg != args)
            cmd = my_strcat_malloc(cmd, " ", true, false);
    }
    return (cmd);
}

static char *get_cmd(cmd_list_t *cmd_list)
{
    char *cmd = NULL;
    int i = 0;

    if (!cmd_list)
        return (NULL);
    for (cmd_list_t *node = cmd_list; i == 0 || node != cmd_list; i += 1) {
        cmd = add_cmd(cmd, node->args);
        cmd = add_redirection(cmd, node);
        node = node->next;
    }
    return (cmd);
}

process_t *init_process_struct(pid_t pid, cmd_list_t *cmd_list)
{
    process_t *process = malloc(sizeof(*process));

    if (process) {
        my_memset(process, 0, sizeof(*process));
        process->pid = pid;
        process->cmd = get_cmd(cmd_list);
    }
    return (process);
}

void destroy_process_struct(process_t *process)
{
    if (!process)
        return;
    free(process->cmd);
    free(process);
}