/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** get_term_line
*/

#include <stdbool.h>
#include "terminal_driver.h"

static void update_history(list_t *history, char *buffer)
{
    if (!history || !buffer || !strlen(buffer))
        return;
    my_put_in_list(history, strdup(buffer), char *);
    while (history->size > HISTORY_SIZE) {
        my_delete_node_from_index(history, -1, free);
    }
}

char *get_term_line(shell_t *shell)
{
    line_t line = {0};

    if (!shell)
        return (NULL);
    line.hist_node = shell->history.start;
    enable_raw_mode();
    while (!(line.completed)) {
        process_key(&line);
    }
    disable_raw_mode();
    update_history(&(shell->history), line.buffer);
    return (line.exit ? NULL : strdup(line.buffer));
}