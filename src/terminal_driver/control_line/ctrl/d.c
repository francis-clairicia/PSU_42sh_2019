/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** d
*/

#include "terminal_driver.h"

void process_ctrl_d(line_t *line)
{
    if (!line)
        return;
    line->completed = true;
    line->exit = true;
}