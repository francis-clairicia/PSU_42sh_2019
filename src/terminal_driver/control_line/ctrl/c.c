/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** c
*/

#include "terminal_driver.h"

void process_ctrl_c(line_t *line)
{
    if (!line)
        return;
    line->completed = true;
    line->index = 0;
    memset(line->buffer, 0, LINE_SIZE);
    line->exit = false;
    write(1, "\n", 2);
}