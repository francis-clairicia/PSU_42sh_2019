/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** process_history_completion
*/

#include "terminal_driver.h"

static void update_history_completion(line_t *line, char *historic_cmd,
                                                    int to_complete_size)
{
    register int size = 0;

    size = my_word_len(line->buffer + line->index);
    reset_line(to_complete_size + 1);
    refresh_line(size);
    my_memset(line->buffer + line->index, 0, size);
    while (historic_cmd[0]) {
        shift_line_right(line, historic_cmd[0]);
        historic_cmd++;
    }
}

bool completion_by_history(line_t *line, char *to_complete,
                                        int to_complete_size)
{
    node_t *node = NULL;
    char *historic_cmd = NULL;

    if (!line || !to_complete)
        return (false);
    node = line->history.start;
    for (; node; node = node->next) {
        historic_cmd = NODE_DATA(node, char *);
        if (!historic_cmd ||
            !my_str_eq_str_n(historic_cmd, to_complete, to_complete_size))
            continue;
        update_history_completion(line, historic_cmd, to_complete_size);
        return (true);
    }
    return (false);
}