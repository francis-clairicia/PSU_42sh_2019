/*
** EPITECH PROJECT, 2020
** unalias.c
** File description:
** unalias built-in command
*/

#include "minishell.h"
#include "my.h"

void destroy_node(alias_t **node)
{
    my_free_array((*node)->cmd);
    free((*node)->alias);
    free(*node);
    *node = NULL;
}

void destroy_every_alias(alias_t **alias_list)
{
    alias_t *temp_list;

    for (; *alias_list; *alias_list = (*alias_list)->next) {
        temp_list = *alias_list;
        destroy_node(&temp_list);
    }
    *alias_list = NULL;
}

void delete_alias(char * const *av, alias_t **alias_l)
{
    alias_t *temp_list = *alias_l;
    alias_t *save_list = *alias_l;

    if (*alias_l && my_array_contains(av + 1, (*alias_l)->alias)) {
        *alias_l = (*alias_l)->next;
        save_list = *alias_l;
        destroy_node(&temp_list);
    }
    for (; *alias_l && (*alias_l)->next;) {
        if (my_array_contains(av + 1, (*alias_l)->next->alias)) {
            temp_list = (*alias_l)->next;
            (*alias_l)->next = (*alias_l)->next->next;
            destroy_node(&temp_list);
            continue;
        }
        *alias_l = (*alias_l)->next;
    }
    *alias_l = save_list;
}

int unalias_builtin_command(char * const *av, shell_t *shell UNUSED)
{
    int ac = my_array_len(av);

    if (ac == 1)
        print_error("unalias", "Too few arguments");
    if (ac >= 2) {
        if (my_array_contains(av + 1, "*"))
            destroy_every_alias(&shell->alias_list);
        else
            delete_alias(av, &shell->alias_list);
    }
    return (0);
}