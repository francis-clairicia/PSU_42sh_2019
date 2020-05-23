/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** apply_vars_to_cmd_list.c
*/

#include "my.h"
#include "mysh_parsing.h"
#include "minishell.h"

static char *find_variable_value(shell_t *shell, error_parse_t *error,
                                const char *variable)
{
    char *value = NULL;

    value = get_var_env(FIND_ENV(shell), variable);
    if (!value && (*error) == NONE)
        (*error) = UNDEFINED_VARIABLE;
    return (value);
}

static bool shift_to_next_var(const char *str, size_t *index)
{
    for (; str[*index]; *index += 1) {
        if (str[*index] == '$' && !IS_CHAR_VAR_STOPPER(str[(*index) + 1]))
            break;
    }
    if (!str[*index])
        return (false);
    *index += 1;
    return (true);
}

static void get_vars_from_to(shell_t *shell, error_parse_t *error,
                            char **str)
{
    size_t index = 0;
    char *var_call = NULL;
    char *var_value = NULL;

    if (my_strlen(*str) <= 1 || (*error) != NONE)
        return;
    if (!shift_to_next_var(*str, &index))
        return;
    if (!my_isalpha((*str)[index])) {
        (*error) = ILLEGAL_VARIABLE_NAME;
        return;
    }
    var_call = my_strdup_until_list_c(&(*str)[index - 1], VAR_STOPPERS);
    var_value = find_variable_value(shell, error, &var_call[1]);
    if ((*error) != NONE)
        return;
    if (!replace_var_call_by_var(str, var_call, var_value))
        return;
    get_vars_from_to(shell, error, str);
}

void apply_vars_to_last_elem(parse_list_t *cur_node, shell_t *shell,
                            error_parse_t *error)
{
    cmd_list_t *last_list = NULL;

    if (!cur_node)
        return;
    last_list = cur_node->cmd_list->prev;
    get_vars_from_to(shell, error, &last_list->redir_input);
    get_vars_from_to(shell, error, &last_list->redir_output);
    if (last_list->args)
        get_vars_from_to(shell, error, &last_list->args->prev->arg);
}