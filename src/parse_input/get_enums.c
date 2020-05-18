/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Gets enum values.
*/

#include "my.h"
#include "mysh_parsing.h"

ssize_t get_redirection_enum(const char *restrict shifted_input)
{
    ssize_t index = 0;
    int size = 0;

    while (redirections[index]) {
        size = my_strlen(redirections[index]);
        if (!my_strncmp(shifted_input, redirections[index], size))
            return (index + 1);
        index += 1;
    }
    return (-1);
}

ssize_t get_splitter_enum(const char *restrict shifted_input)
{
    ssize_t index = 0;
    int size = 0;

    while (splitters[index]) {
        size = my_strlen(splitters[index]);
        if (!my_strncmp(shifted_input, splitters[index], size))
            return (index + 1);
        index += 1;
    }
    return (-1);
}