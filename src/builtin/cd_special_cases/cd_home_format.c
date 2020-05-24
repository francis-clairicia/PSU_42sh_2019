/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** cd_home_format.c
*/

#include <stdbool.h>
#include "my.h"
#include "minishell.h"

bool change_dir_through_home(shell_t *shell, char const *arg)
{
    char *home_var = NULL;
    char *tmp_arg = NULL;

    home_var = get_var_env(shell->envp, "HOME");
    if (!home_var) {
        my_putstr_error("No $HOME variable set.\n");
        return (false);
    }
    tmp_arg = my_strcat_malloc(home_var, (char *)&arg[1], 0, 0);
    if (chdir(tmp_arg) < 0) {
        print_error(tmp_arg, strerror(errno));
        if (tmp_arg)
            free(tmp_arg);
        return (false);
    }
    if (tmp_arg)
        free(tmp_arg);
    return (true);
}

bool eligible_for_home(char const *arg)
{
    if (!arg || !arg[0])
        return (false);
    return (arg[0] == '~' && (!arg[1] || arg[1] == '/'));
}