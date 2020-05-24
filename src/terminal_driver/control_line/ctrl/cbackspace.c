/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** backspace
*/

#include "terminal_driver.h"

void shift_line_left(line_t *line);

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
