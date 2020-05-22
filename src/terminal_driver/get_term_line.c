/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** get_term_line
*/

#include <stdbool.h>
#include "terminal_driver.h"

char *get_term_line(void)
{
    line_t line = {0};

    while (!(line.completed)) {
        process_key(&line);
    }
    printf("\r%s\n", line.buffer);
    return (line.exit ? NULL : strdup(line.buffer));
}