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
    write(1, "\b \b", 3);
}

void process_ctrl_q(line_t *line)
{
    if (!line)
        return;
    exit(0);
}

void process_enter(line_t *line)
{
    if (!line)
        return;
    line->completed = true;
    write(1, "\r\n", 2);
}