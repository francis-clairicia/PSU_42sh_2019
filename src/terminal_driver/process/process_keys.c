/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** process_keys
*/

#include "terminal_driver.h"
#include "keys_template.h"
#include "redirect_process_key.h"

static int sequence_key(void)
{
    char seq_read[2] = {0};

    if (read(STDIN_FILENO, seq_read, 2) != 2)
        return ('\x1b');
    if (seq_read[0] != '[')
        return ('\x1b');
    return (find_seq_key(seq_read[1]));
}

static int read_key(void)
{
    char c_read = 0;
    int n_read = 0;

    do {
        n_read = read(STDIN_FILENO, &c_read, 1);
        if (n_read == -1 && errno != EAGAIN)
            die("Read error");
    } while (n_read != 1);
    if (c_read == '\x1b')
        return (sequence_key());
    return (c_read);
}

void process_key(line_t *line)
{
    int key = read_key();
    int redirect_index = 0;

    if (!line)
        return;
    redirect_index = get_redirect_key_idx(key);
    if (redirect_index == -1 && isprint(key)) {
        shift_line_right(line, key);
    } else if (redirect_index != -1) {
        redirect_process_key[redirect_index](line);
    }
}