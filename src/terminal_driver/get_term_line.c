/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** get_term_line
*/

#include <stdbool.h>
#include "terminal_driver.h"

char *get_term_line(shell_t *shell UNUSED)
{
    line_t line = {0};

    if (!shell)
        return (NULL);
    line.history = &(shell->history);
    enable_raw_mode();
    while (!(line.completed)) {
        process_key(&line);
    }
    my_put_in_list(&(shell->history), strdup(line.buffer), char *);
    disable_raw_mode();
    //for (node_t *node = shell->history.start; node; node = node->next) {
    //    printf("%s\n", NODE_DATA(node, char *));
    //}
    return (line.exit ? NULL : strdup(line.buffer));
}