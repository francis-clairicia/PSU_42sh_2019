/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** right
*/

#include "terminal_driver.h"

void process_arrow_right(line_t *line)
{
    if (!line)
        return;
    if (line->index >= LINE_SIZE - 2 ||
        !(line->buffer[line->index]))
        return;
    write(1, "\x1b[1C", 4);
    line->index++;
}

void process_ctrl_arrow_right(line_t *line)
{
    bool blank_save = false;

    if (!line)
        return;
    if (line->index >= LINE_SIZE - 2 ||
        !(line->buffer[line->index]))
        return;
    blank_save = isblank(line->buffer[line->index]) ? true : false;
    while ((!isblank(line->buffer[line->index]) ^ blank_save) &&
        line->index < LINE_SIZE - 2 && line->buffer[line->index]) {
        write(1, "\x1b[1C", 4);
        line->index++;
    }
}