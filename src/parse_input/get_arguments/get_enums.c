/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** Gets enum values to match characters.
*/

#include "my.h"
#include "mysh_parsing.h"

redirection_type_t get_redirection_enum(const char *restrict shifted_input,
                                        int *size)
{
    register size_t index = 0;
    redirection_type_t cur_type = 1;

    while (REDIRECTIONS_ARRAY[index]) {
        *size = my_strlen(REDIRECTIONS_ARRAY[index]);
        if (!my_strncmp(shifted_input, REDIRECTIONS_ARRAY[index], *size))
            return (cur_type);
        index += 1;
        cur_type <<= 1;
    }
    return (NONE);
}

splitter_type_t get_splitter_enum(const char *restrict shifted_input,
                                int *size)
{
    splitter_type_t index = 0;

    while (SPLITTERS_ARRAY[index]) {
        *size = my_strlen(SPLITTERS_ARRAY[index]);
        if (!my_strncmp(shifted_input, SPLITTERS_ARRAY[index], *size))
            return (index + 1);
        index += 1;
    }
    return (0);
}
