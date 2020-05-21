/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** find_binary_in_path.c
*/

#include "minishell.h"

static char *free_and_returns(char **word_array, char *str)
{
    my_free_array(word_array);
    return (str);
}

char *find_binary_in_path(char const *binary, char * const *envp)
{
    char *path_variable = get_var_env(envp, "PATH");
    char **path_list = my_str_to_word_array(path_variable, ":");
    char *path_concat = NULL;
    int i = 0;

    while (binary != NULL && path_list != NULL && path_list[i] != NULL) {
        path_concat = join_path(path_list[i], binary);
        if (path_concat != NULL && access(path_concat, F_OK) == 0)
            return (free_and_returns(path_list, path_concat));
        free(path_concat);
        i += 1;
    }
    print_error(binary, "Command not found");
    return (free_and_returns(path_list, NULL));
}