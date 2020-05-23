/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** down
*/

#include "terminal_driver.h"

static void clear_line(line_t *line, node_t *node)
{
    register int index = 0;
    register int cmd_size = 0;

    if (line->index > 0)
        printf("\x1b[%dD", line->index);
    fflush(stdout);
    if (!node)
        return;
    cmd_size = my_strlen(NODE_DATA(node, char *));
    for (; index < cmd_size; index += 1)
        write(1, " ", 1);
    printf("\x1b[%dD", cmd_size);
    fflush(stdout);
}

void process_arrow_down(line_t *line)
{
    char *new_cmd = NULL;
    node_t *cur_node = NULL;

    if (!line || !(line->hist_node) || !(line->hist_node->previous) ||
        !(line->hist_node->previous->previous))
        return;
    cur_node = line->hist_node->previous;
    new_cmd = NODE_DATA(cur_node->previous, char *);
    clear_line(line, cur_node);
    if (new_cmd)
        printf(new_cmd);
    fflush(stdout);
    line->index = my_strlen(new_cmd);
    memset(line->buffer, 0, LINE_SIZE);
    my_strcpy(line->buffer, new_cmd);
    line->hist_node = cur_node;
}