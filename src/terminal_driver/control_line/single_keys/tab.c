/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** tab
*/

#include "terminal_driver.h"

static char *get_word_to_complete(line_t *line, int *size)
{
    int tmp_index = line->index;

    if (!size)
        return;
    while (tmp_index > 0 && line->buffer[tmp_index] != ' ' ||
                            line->buffer[tmp_index] != '\t') {
        if (line->buffer[tmp_index] == '!') {
            *size = line->index - tmp_index;
            return (line->buffer + tmp_index);
        }
        tmp_index--;
    }
    return (NULL);
}

static void completion_by_history(line_t *line, char *to_complete,
                                                int to_complete_size)
{
    node_t *node = line->history.start;
    char *historic_cmd = NULL;

    for (; node; node = node->next) {
        historic_cmd = NODE_DATA(node, char *);
        if (!historic_cmd ||
            my_strncmp(to_complete, historic_cmd, to_complete_size))
            continue;
        refresh_line(to_complete_size + 1);
        while (historic_cmd[0]) {
            shift_line_right(line, historic_cmd[0]);
            historic_cmd++;
        }
        break;
    }
}

void process_tabulation(line_t *line)
{
    char *to_complete = NULL;
    int to_complete_size = 0;

    if (!line)
        return;
    to_complete = get_word_to_complete(line, &to_complete_size);
    if (!to_complete)
        return;
    completion_by_history(line, to_complete, to_complete_size);
}