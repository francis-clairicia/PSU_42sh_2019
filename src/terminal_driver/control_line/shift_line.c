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
    register int size = 0;

    if (line->index <= 0)
        return;
    strncpy(cpy_buff, line->buffer + line->index, LINE_SIZE - line->index);
    strcpy(line->buffer + line->index - 1, cpy_buff);
    size = strlen(cpy_buff);
    printf("\b \b%s \x1b[%dD", cpy_buff, size + 1);
    line->index--;
    fflush(stdout);
}

void shift_line_right(line_t *line, int key)
{
    char cpy_buff[LINE_SIZE] = {0};
    register int size = 0;

    if (line->index >= LINE_SIZE - 1)
        return;
    strncpy(cpy_buff, line->buffer + line->index, LINE_SIZE - line->index);
    strncpy(line->buffer + line->index + 1, cpy_buff,
                                                LINE_SIZE - line->index - 1);
    line->buffer[line->index] = key;
    my_putstr(line->buffer + line->index);
    size = my_strlen(line->buffer + line->index);
    if (size > 1)
        printf("\x1b[%dD", size - 1);
    line->index++;
    fflush(stdout);
}