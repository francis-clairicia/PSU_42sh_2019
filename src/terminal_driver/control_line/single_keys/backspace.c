/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** backspace
*/

#include "terminal_driver.h"

void process_backspace(line_t *line)
{
    if (!line)
        return;
    if (line->index <= 0)
        return;
    shift_line_left(line);
}