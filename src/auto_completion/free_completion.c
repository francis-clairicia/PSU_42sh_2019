/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** free_completion
*/

#include "auto_completion.h"

void free_completion(auto_completion_t *completion)
{
    if (!completion)
        return;
    if (completion->completion)
        free(completion->completion);
}