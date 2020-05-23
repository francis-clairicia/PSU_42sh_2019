/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** special_keys
*/

#include "terminal_driver.h"

void shift_line_left(line_t *line);

void process_backspace(line_t *line)
{
    if (!line)
        return;
    if (line->index <= 0)
        return;
    shift_line_left(line);
}

void process_ctrl_backspace(line_t *line)
{
    if (!line || line->index <= 0)
        return;
    if (isblank(line->buffer[line->index - 1])) {
        while (line->index > 0 && isblank(line->buffer[line->index - 1]) &&
            line->buffer[line->index - 1]) {
            shift_line_left(line);
        }
    } else {
        while (line->index > 0 && !isblank(line->buffer[line->index - 1]) &&
            line->buffer[line->index - 1]) {
            shift_line_left(line);
        }
    }
}

void process_enter(line_t *line)
{
    if (!line)
        return;
    line->completed = true;
    line->index = 0;
    write(1, "\r\n", 2);
}