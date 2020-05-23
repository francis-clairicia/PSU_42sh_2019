/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** Adds arguments to a list from a matching string containing wildcards.
*/

#include <stdlib.h>
#include <dirent.h>
#include "my.h"
#include "mysh_parsing.h"

static void free_args_match_resources(file_extent_t file, DIR *directory)
{
    if (file.path)
        free(file.path);
    if (file.file)
        free(file.file);
    if (directory)
        closedir(directory);
}

static bool setup_matching(const char *match_str, DIR **directory,
                            file_extent_t *file)
{
    if (!match_str)
        return (false);
    file->path = get_path_from_str(match_str);
    file->file = get_matching_from_str(match_str);
    (*directory) = opendir((file->path) ? file->path : "./");
    if (!(*directory))
        return (false);
    return (true);
}

static void examinate_directory_files(DIR **directory, file_extent_t root_file,
                                    globbing_match_t *matching,
                                    argument_globber_t globber)
{
    struct dirent *stat = NULL;
    arguments_t *new_arg = NULL;
    char *path_cur_file = NULL;

    stat = readdir(*directory);
    for (; stat; stat = readdir(*directory)) {
        if (!stat->d_name || stat->d_name[0] == '.')
            continue;
        path_cur_file = my_strcat_malloc(root_file.path, stat->d_name, 0, 0);
        if (match(matching->str, path_cur_file)) {
            matching->treated = true;
            new_arg = add_arg_list_node_index(globber.head, globber.cur_node);
            new_arg->arg = path_cur_file;
        } else {
            if (path_cur_file)
                free(path_cur_file);
        }
    }
}

bool add_args_for_matching(arguments_t **head, arguments_t *tmp)
{
    file_extent_t root_file = {.path = NULL, .file = NULL};
    globbing_match_t matching;
    argument_globber_t globber = {.head = head, .cur_node = tmp};
    DIR *directory = NULL;

    if (!head || !tmp)
        return (false);
    matching = (globbing_match_t){.str = tmp->arg, .treated = false};
    if (!setup_matching(matching.str, &directory, &root_file))
        return (false);
    examinate_directory_files(&directory, root_file, &matching, globber);
    free_args_match_resources(root_file, directory);
    return (matching.treated);
}
