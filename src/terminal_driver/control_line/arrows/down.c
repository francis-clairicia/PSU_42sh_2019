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

static bool load_history_node(line_t *line)
{
    if (!line)
        return (false);
    if (!(line->hist_node))
        return (false);
    if (!(line->hist_node->previous))
        return (false);
    line->hist_node = line->hist_node->previous;
    return (true);
}

void process_arrow_down(line_t *line)
{
    char *new_cmd = NULL;

    if (!load_history_node(line))
        return;
    new_cmd = NODE_DATA(line->hist_node, char *);
    clear_line(line, line->hist_node->next);
    if (new_cmd)
        printf(new_cmd);
    fflush(stdout);
    line->index = my_strlen(new_cmd);
    memset(line->buffer, 0, LINE_SIZE);
    my_strcpy(line->buffer, new_cmd);
}