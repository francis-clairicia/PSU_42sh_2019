/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** auto_completion
*/

#ifndef AUTO_COMPLETION_H_
#define AUTO_COMPLETION_H_

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include "dcll.h"

typedef struct auto_completion_s
{
    dcll_t dcll;
    char *completion;
} auto_completion_t;

bool find_completion(char *path, auto_completion_t **list);

char *get_path_from_str(const char *str);
char *get_matching_from_str(const char *str);

void free_completion(auto_completion_t *completion);

#endif /* !AUTO_COMPLETION_H_ */