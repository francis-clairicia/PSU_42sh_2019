/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** add_args_for_matching.c
*/

#include <stdlib.h>
#include <dirent.h>
#include "my.h"
#include "mysh_parsing.h"

static void free_args_match_resources(char *path, char *matching,
                                        DIR *directory)
{
    if (path)
        free(path);
    if (matching)
        free(matching);
    if (directory)
        closedir(directory);
}

static void check_to_add_arg(arguments_t **args, const char *match_str,
                            const char *path, const char *cur_file_name)
{
    char *path_cur_file = NULL;

    path_cur_file = my_strcat_malloc(path, cur_file_name, 0, 0);
    if (match(match_str, path_cur_file)) {
        add_arg_list_node(args);
        (*args)->prev->arg = path_cur_file;
    } else {
        if (path_cur_file)
            free(path_cur_file);
    }
}

void add_args_for_matching(arguments_t **args, const char *match_str)
{
    DIR *directory = NULL;
    struct dirent *stat = NULL;
    char *path = NULL;
    char *matching = NULL;

    if (!match_str)
        return;
    path = get_path_from_str(match_str);
    if (!path)
        path = my_strdup("./");
    matching = get_matching_from_str(match_str);
    directory = opendir(path);
    for (stat = readdir(directory); stat; stat = readdir(directory)) {
        if (!stat->d_name)
            continue;
        check_to_add_arg(args, match_str, path, stat->d_name);
    }
    free_args_match_resources(path, matching, directory);
}
