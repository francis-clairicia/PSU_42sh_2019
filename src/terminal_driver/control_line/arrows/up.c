/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** up
*/

#include "terminal_driver.h"

static void clear_line(line_t *line, int cmd_size)
{
    register int index = 0;

    if (line->index > 0)
        printf("\x1b[%dD", line->index);
    for (; index < cmd_size; index += 1) {
        write(1, " ", 1);
    }
    printf("\x1b[%dD", cmd_size);
}

void process_arrow_up(line_t *line)
{
    char *new_cmd = NULL;
    int cmd_size = 0;

    if (!line || !(line->history) ||
        !(line->history->start))
        return;
    new_cmd = NODE_DATA(line->history->start, char *);
    if (!new_cmd)
        return;
    cmd_size = strlen(new_cmd);
    clear_line(line, cmd_size);
    printf(new_cmd);
    fflush(stdout);
    line->index = cmd_size;
    memset(line->buffer, 0, LINE_SIZE);
    strcpy(line->buffer, new_cmd);
    rotate_begin_list(line->history);
}