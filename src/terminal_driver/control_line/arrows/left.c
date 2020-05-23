/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** left
*/

#include "terminal_driver.h"

void process_arrow_left(line_t *line)
{
    if (!line)
        return;
    if (line->index <= 0)
        return;
    write(1, "\x1b[1D", 4);
    line->index--;
}

void process_ctrl_arrow_left(line_t *line)
{
    bool blank_save = false;

    if (!line)
        return;
    if (line->index <= 0)
        return;
    blank_save = isblank(line->buffer[line->index - 1]) ? true : false;
    while ((!isblank(line->buffer[line->index - 1]) ^ blank_save) &&
        line->index > 0) {
        write(1, "\x1b[1D", 4);
        line->index--;
    }
}