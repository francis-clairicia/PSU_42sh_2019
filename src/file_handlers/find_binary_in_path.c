/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** find_binary_in_path.c
*/

#include "minishell.h"

char *find_binary_in_path(char const *binary, char * const *path_list)
{
    char *path_concat = NULL;
    int i = 0;

    while (binary != NULL && path_list != NULL && path_list[i] != NULL) {
        path_concat = join_path(path_list[i], binary);
        if (path_concat != NULL && access(path_concat, F_OK) == 0)
            return (path_concat);
        free(path_concat);
        i += 1;
    }
    print_error(binary, "Command not found");
    return (NULL);
}