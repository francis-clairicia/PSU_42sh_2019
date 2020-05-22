/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** get_path_to_executable.c
*/

#include "minishell.h"

static int check_access(char const *filepath)
{
    struct stat infos;

    if (filepath == NULL)
        return (0);
    if (stat(filepath, &infos) < 0) {
        print_error(filepath, "Command not found");
        return (0);
    } else if (access(filepath, X_OK) < 0) {
        print_error(filepath, strerror(errno));
        return (0);
    }
    if (S_ISDIR(infos.st_mode)) {
        print_error(filepath, "Permission denied");
        return (0);
    }
    return (1);
}

char *get_path_to_executable(char const *binary, char * const *path_list)
{
    char *filepath = NULL;

    if (my_strchr_index(binary, '/') >= 0) {
        if (!check_access(binary))
            return (NULL);
        return (my_strdup(binary));
    }
    filepath = find_binary_in_path(binary, path_list);
    if (!check_access(filepath)) {
        free(filepath);
        return (NULL);
    }
    return (filepath);
}