/*
** EPITECH PROJECT, 2020
** alias.c
** File description:
** alias built-in command
*/

#include "minishell.h"
#include "my.h"

void show_alias(char const *alias_arg, alias_t *alias_list)
{
    list_t cmd_list;
    char *concat_cmd_list = NULL;
    int len;
    alias_t *temp_list = alias_list;

    for (; temp_list; temp_list = temp_list->next) {
        if (!my_strcmp(temp_list->alias, alias_arg)) {
            cmd_list = my_2d_array_to_list(temp_list->cmd);
            concat_cmd_list = my_concat_str_list(
            cmd_list, ' ', &len);
            my_printf("%s\n", concat_cmd_list);
            my_free_list(&cmd_list, NULL);
            free(concat_cmd_list);
        }
    }
}

int modify_alias(char * const *av, alias_t **alias_list)
{
    alias_t *temp_list = *alias_list;

    for (; *alias_list; *alias_list = (*alias_list)->next) {
        if (!my_strcmp((*alias_list)->alias, av[1])) {
            my_free_array((*alias_list)->cmd);
            (*alias_list)->cmd = my_array_dup(av + 2);
            *alias_list = temp_list;
            return (1);
        }
    }
    *alias_list = temp_list;
    return (0);
}

void add_alias_to_list(char * const *av, alias_t **alias_list)
{
    alias_t *temp_list = NULL;
    alias_t *save_list = *alias_list;

    if (modify_alias(av, alias_list))
        return ;
    temp_list = malloc(sizeof(alias_t));
    temp_list->cmd = my_array_dup(av + 2);
    temp_list->alias = my_strdup(av[1]);
    temp_list->next = NULL;
    if (!(*alias_list)) {
        *alias_list = temp_list;
        return ;
    }
    for (; (*alias_list)->next; *alias_list = (*alias_list)->next);
    (*alias_list)->next = temp_list;
    *alias_list = save_list;
}

void print_alias_list(alias_t *alias_list)
{
    alias_t *temp_list = alias_list;
    int cmd_len;
    list_t cmd_list;
    char *concat_cmd_list = NULL;
    int len;

    for (; temp_list; temp_list = temp_list->next) {
        cmd_len = my_array_len(temp_list->cmd);
        my_printf("%s    ", temp_list->alias);
        if (cmd_len > 1) {
            cmd_list = my_2d_array_to_list(temp_list->cmd);
            concat_cmd_list = my_concat_str_list(
                cmd_list, ' ', &len);
            my_printf("(%s)\n", concat_cmd_list);
            my_free_list(&cmd_list, NULL);
            free(concat_cmd_list);
        } else if (cmd_len == 1)
            my_printf("%s\n", temp_list->cmd[0]);
    }
}

int alias_builtin_command(char * const *av, shell_t *shell)
{
    int ac = my_array_len(av);

    if (ac == 1)
        print_alias_list(shell->alias_list);
    if (ac == 2)
        show_alias(av[1], shell->alias_list);
    if (ac >= 3) {
        if (my_mass_strcmp(av[1], "alias", "unalias")) {
            print_error(av[1], "Too dangerous to alias that");
            return (set_exit_status(shell, 1));
        }
        add_alias_to_list(av, &shell->alias_list);
    }
    return (set_exit_status(shell, 0));
}