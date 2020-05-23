/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** find_completion
*/

#include "auto_completion.h"

static DIR *open_dir_from_path(char * path)
{
    char *dir_path = get_path_from_str(path);
    DIR *dir = NULL;

    if (!path || !dir_path)
        return (NULL);
    dir = opendir(dir_path);
    free(dir_path);
    return (dir);
}

static bool add_completion(auto_completion_t **list, char *letion,
                                                    bool is_folder)
{
    auto_completion_t *new = {0};

    if (!list || !letion)
        return (false);
    new = DCLL_ADD(list, sizeof(auto_completion_t), free_completion);
    if (!new)
        return (false);
    if (is_folder) {
        letion[strlen(letion)] = '/';
        letion[strlen(letion) + 1] = 0;
    }
    new->completion = strdup(letion);
    if (!(new->completion))
        return (false);
    return (true);
}

bool find_completion(char *path, auto_completion_t **list)
{
    DIR *dir = open_dir_from_path(path);
    struct dirent *dirent = NULL;
    char *comp = get_matching_from_str(path);

    if (!list || !path || !dir || !comp)
        return (false);
    do {
        dirent = readdir(dir);
        if (!dirent)
            break;
        if (!strncmp(comp, dirent->d_name, strlen(comp)) &&
            dirent->d_name[0] != '.' &&
            !add_completion(list, dirent->d_name + strlen(comp),
                        dirent->d_type == DT_DIR ? true : false))
            return (false);
    } while (dirent);
    free(comp);
    closedir(dir);
    return (true);
}