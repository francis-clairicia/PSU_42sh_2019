/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** redirect_process_key
*/

#ifndef REDIRECT_PROCESS_KEY_H_
#define REDIRECT_PROCESS_KEY_H_

#include "terminal_driver.h"

void process_arrow_left(line_t *line);
void process_arrow_right(line_t *line);
void process_ctrl_arrow_left(line_t *line);
void process_ctrl_arrow_right(line_t *line);
void process_arrow_up(line_t *line);
void process_arrow_down(line_t *line);
void process_backspace(line_t *line);
void process_ctrl_backspace(line_t *line);
void process_ctrl_q(line_t *line);
void process_ctrl_c(line_t *line);
void process_ctrl_d(line_t *line);
void process_enter(line_t *line);

static void (*redirect_process_key[])(line_t *) = {
    process_arrow_left,
    process_arrow_right,
    process_ctrl_arrow_left,
    process_ctrl_arrow_right,
    process_arrow_up,
    process_arrow_down,
    process_backspace,
    process_ctrl_backspace,
    process_ctrl_q,
    process_ctrl_c,
    process_ctrl_d,
    process_enter
};

static const int redirect_key_template[] =
{
    ARROW_LEFT,
    ARROW_RIGHT,
    CTRL_ARROW_LEFT,
    CTRL_ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    BACKSPACE,
    0x08,
    CTRL_KEY('q'),
    0x03,
    0x04,
    '\r'
};

static inline int get_redirect_key_idx(int key)
{
    size_t size = sizeof(redirect_key_template) /
                    sizeof(redirect_key_template[0]);
    size_t index = 0;

    for (; index < size; index += 1) {
        if (key == redirect_key_template[index])
            return (index);
    }
    return (-1);
}

#endif /* !REDIRECT_PROCESS_KEY_H_ */