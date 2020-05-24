/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** process_file_completion
*/

#include "terminal_driver.h"

static void update_file_completion(line_t *line, char *file_name,
                                            int to_complete_size)
{
    register int size = 0;

    size = my_word_len(line->buffer + line->index);
    reset_line(to_complete_size);
    refresh_line(size);
    my_strcpy(line->buffer + line->index + size, file_name);
    my_putstr(line->buffer + line->index);
    line->index += size + strlen(file_name);
}

bool completion_by_files(line_t *line, char *to_complete,
                                        int to_complete_size)
{
    auto_completion_t *node = NULL;

    if (!line || !to_complete)
        return (false);
    if (!find_completion(to_complete, &node))
        return (false);
    for (; node; node = DCLL_NEXT_C(node, auto_completion_t *)) {
        if (!node || !(node->completion))
            continue;
        update_file_completion(line, node->completion, to_complete_size);
        DCLL_FREE_LIST(node);
        return (true);
    }
    DCLL_FREE_LIST(node);
    return (false);
}