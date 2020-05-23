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
    char seq_read[5] = {0};
    int n_read = 0;

    n_read = read(STDIN_FILENO, seq_read, sizeof(seq_read));
    if (seq_read[0] == '[' && n_read == 2)
        return (find_template_key(seq_template, seq_read[1]));
    if (!strncmp("[1;5", seq_read, 4) && n_read == 5)
        return (find_template_key(ctrl_seq_template, seq_read[4]));
    return ('\x1b');
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
    if (redirect_index == -1 && isprint(key) && line->index <= LINE_SIZE - 2) {
        shift_line_right(line, key);
    } else if (redirect_index != -1) {
        redirect_process_key[redirect_index](line);
    }
}