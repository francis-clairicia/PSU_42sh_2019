/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** q
*/

#include "terminal_driver.h"

void process_ctrl_q(line_t *line)
{
    if (!line)
        return;
    line->exit = true;
    line->completed = true;
}