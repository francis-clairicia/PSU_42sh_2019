/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** parse_input.c
*/

#include "minishell.h"

static char **make_argv_from_arg_list(arguments_t *args)
{
    list_t list = my_list();
    arguments_t *node = args;

    for (int i = 0; i == 0 || node != args; node = node->next, i += 1) {
        my_append_to_list(&list, my_strdup(node->arg), char *);
    }
    return (my_list_to_2d_array(&list, true));
}

static void init_new_command(cmd_list_t *node, list_t *list)
{
    command_t command = init_command_struct();

    command.input_fd = get_input_fd(node->redir_name, node->redir_type);
    command.output_fd = get_output_fd(node->redir_name, node->redir_type);
    command.argv = make_argv_from_arg_list(node->args);
    my_append_to_list(list, command, command_t);
}

static command_t *create_command_list(list_t *list)
{
    int i = 0;
    command_t *commands = malloc(sizeof(command_t) * (list->size + 1));

    if (commands) {
        for (node_t *node = list->start; node; node = node->next, i += 1)
            commands[i] = NODE_DATA(node, command_t);
        commands[list->size] = init_command_struct();
    }
    my_free_list(list, NULL);
    return (commands);
}

command_t *parse_cmd_list(cmd_list_t *cmd_list, int *nb_commands)
{
    list_t list = my_list();
    cmd_list_t *node = cmd_list;

    if (cmd_list == NULL || nb_commands == NULL)
        return (NULL);
    for (int i = 0; i == 0 || node != cmd_list; node = node->next, i += 1)
        init_new_command(node, &list);
    *nb_commands = list.size;
    return (create_command_list(&list));
}