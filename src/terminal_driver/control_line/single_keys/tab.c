/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** tab
*/

#include "terminal_driver.h"

static char *get_word_to_complete(line_t *line, int *size, bool *is_hist)
{
    int tmp_index = line->index;

    if (!size || !is_hist)
        return (NULL);
    while (tmp_index >= 0 && (line->buffer[tmp_index] != ' ' ||
                            line->buffer[tmp_index] != '\t')) {
        if (line->buffer[tmp_index] == '!') {
            *size = line->index - tmp_index - 1;
            line->index = tmp_index;
            *is_hist = true;
            return (line->buffer + tmp_index + 1);
        } else if (tmp_index == 0 || line->buffer[tmp_index - 1] == ' ' ||
            line->buffer[tmp_index - 1] == '\t') {
            *size = line->index - tmp_index;
            line->index = tmp_index;
            return (line->buffer + tmp_index);
        }
        tmp_index--;
    }
    return (NULL);
}

void process_tabulation(line_t *line)
{
    char *to_complete = NULL;
    int to_complete_size = 0;
    int index_save = 0;
    bool is_hist = false;

    if (!line)
        return;
    index_save = line->index;
    to_complete = get_word_to_complete(line, &to_complete_size, &is_hist);
    if (!to_complete) {
        line->index = index_save;
        return;
    }
    if ((is_hist &&
        !completion_by_history(line, to_complete, to_complete_size)) ||
        (!is_hist &&
        !completion_by_files(line, to_complete, to_complete_size)))
        line->index = index_save;
}