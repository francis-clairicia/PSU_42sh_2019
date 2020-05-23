/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** up
*/

#include "terminal_driver.h"

static void clear_line(line_t *line, node_t *node)
{
    register int cmd_size = 0;

    reset_line(line->index);
    fflush(stdout);
    if (!node)
        return;
    cmd_size = my_strlen(NODE_DATA(node, char *));
    refresh_line(cmd_size + line->index);
}

static bool load_history_node(line_t *line)
{
    if (!line)
        return (false);
    if (!(line->hist_node))
        line->hist_node = line->history.start;
    else if (line->hist_node->next)
        line->hist_node = line->hist_node->next;
    if (!(line->hist_node))
        return (false);
    return (true);
}

void process_arrow_up(line_t *line)
{
    char *new_cmd = NULL;

    if (!load_history_node(line))
        return;
    new_cmd = NODE_DATA(line->hist_node, char *);
    clear_line(line, line->hist_node->previous);
    if (new_cmd)
        printf(new_cmd);
    fflush(stdout);
    line->index = my_strlen(new_cmd);
    memset(line->buffer, 0, LINE_SIZE);
    my_strcpy(line->buffer, new_cmd);
}