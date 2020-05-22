/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** arrow_keys
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
    register int offset = 0;

    if (!line)
        return;
    if (line->index <= 0)
        return;
    for (; !isblank(line->buffer[line->index + offset]) &&
                    line->index + offset > 0; offset -= 1);
    printf("\x1b[%dD", -offset);
    fflush(stdout);
    line->index += offset;
}

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
    register int offset = 0;

    if (!line)
        return;
    if (line->index >= LINE_SIZE - 2 ||
        !(line->buffer[line->index]))
        return;
    for (; !isblank(line->buffer[line->index + offset]) &&
        line->index + offset < LINE_SIZE - 1 &&
        line->buffer[line->index + offset]; offset += 1);
    printf("\x1b[%dC", offset);
    fflush(stdout);
    line->index += offset;
}