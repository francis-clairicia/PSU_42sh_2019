/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** reset_line
*/

#include "terminal_driver.h"

void reset_line(int size)
{
    register int index = 0;

    for (; index < size; index += 1) {
        my_putstr("\x1b[1D \x1b[1D");
    }
}

void refresh_line(int size)
{
    register int index = 0;

    for (; index < size; index += 1) {
        my_putstr(" ");
    }
    reset_line(size);
}