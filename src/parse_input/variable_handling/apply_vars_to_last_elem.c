/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** apply_vars_to_cmd_list.c
*/

#include "my.h"
#include "mysh_parsing.h"
#include "minishell.h"

static bool get_vars_from_to(char * const * envp, char **str)
{
    size_t index = 0;
    char *asked_var = NULL;
    char *env_var = NULL;

    if (my_strlen(*str) <= 1)
        return (true);
    for (; (*str)[index]; index += 1) {
        if ((*str)[index] == '$' && (*str)[index + 1]
            && ((*str)[index + 1] != '/' && !is_char_spaces((*str)[index + 1])))
            break;
    }
    if (!(*str)[index])
        return (true);
    if (!my_isalpha((*str)[index])) {
        my_putstr("Illegal variable name.\n");
        return (false);
    }
    env_var = get_var_env(envp, asked_var);
    return (get_vars_from_to(envp, &str[index]));
}

bool apply_vars_to_last_elem(parse_list_t *cur_node, char * const *envp)
{
    cmd_list_t *last_list = NULL;

    if (!cur_node)
        return (true);
    last_list = cur_node->cmd_list->prev;
    if (!get_vars_from_to(envp, &last_list->redir_input))
        return (false);
    if (!get_vars_from_to(envp, &last_list->redir_output))
        return (false);
    return (true);
}