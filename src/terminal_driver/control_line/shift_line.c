/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** shift_line
*/

#include "terminal_driver.h"
#include "my.h"

void shift_line_left(line_t *line)
{
    char cpy_buff[LINE_SIZE] = {0};

    if (line->index <= 0)
        return;
    memcpy(cpy_buff, line->buffer + line->index, LINE_SIZE - line->index);
    memcpy(line->buffer + line->index - 1, cpy_buff, LINE_SIZE - line->index);
    line->index--;
}

void shift_line_right(line_t *line, int key)
{
    char cpy_buff[LINE_SIZE] = {0};

    if (line->index >= LINE_SIZE - 1)
        return;
    strncpy(cpy_buff, line->buffer + line->index, LINE_SIZE - line->index);
    strncpy(line->buffer + line->index + 1, cpy_buff,
                                                LINE_SIZE - line->index - 1);
    line->buffer[line->index] = key;
    write(1, &key, 1);
    line->index++;
}