/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** enter
*/

#include "terminal_driver.h"

void process_enter(line_t *line)
{
    if (!line)
        return;
    line->completed = true;
    line->index = 0;
    write(1, "\n", 2);
}