/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** print_git_branch.c
*/

#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include "minishell.h"

static char const *get_filename(char const *file)
{
    int slash = 0;

    while ((slash = my_strchr_index(file, '/')) >= 0)
        file = &file[slash + 1];
    return (file);
}

static char *get_basedir(char const *path)
{
    int index = my_strlen(path) - 1;

    if (index == 0)
        return (NULL);
    while (index > 0 && path[index] == '/')
        index -= 1;
    while (index >= 0 && path[index] != '/')
        index -= 1;
    return (my_strndup(path, index + 1));
}

static char *get_git_path(char const *cwd)
{
    DIR *dir = opendir(cwd);
    struct dirent *ent = NULL;
    char *basedir = NULL;
    char *path = NULL;

    if (!dir)
        return (NULL);
    while ((ent = readdir(dir))) {
        if (my_strcmp(ent->d_name, ".git") == 0) {
            closedir(dir);
            return (join_path(cwd, ".git"));
        }
    }
    closedir(dir);
    basedir = get_basedir(cwd);
    if (basedir && my_strcmp(basedir, "/") != 0)
        path = get_git_path(basedir);
    free(basedir);
    return (path);
}

void print_git_branch(char const *cwd)
{
    char *head_path = NULL;
    char *line = NULL;
    int fd = 0;
    char *git_path = (!cwd) ? NULL : get_git_path(cwd);

    if (git_path == NULL)
        return;
    head_path = join_path(git_path, "HEAD");
    if (head_path) {
        fd = open(head_path, O_RDONLY);
        if (get_next_line_2(&line, fd)) {
            my_printf(" (%s)", get_filename(line));
            free(line);
        }
        if (fd != -1)
            close(fd);
        free(head_path);
    }
    free(git_path);
}