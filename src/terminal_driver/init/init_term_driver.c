/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** init_term_driver
*/

#include "terminal_driver.h"

void disable_raw_mode(void)
{
    static struct termios save = {0};
    char cmp_buf[sizeof(struct termios)] = {0};

    if (!memcmp(&save, cmp_buf, sizeof(struct termios))) {
        tcgetattr(STDIN_FILENO, &save);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &save);
}

void enable_raw_mode(void)
{
    struct termios raw = {0};

    tcgetattr(STDIN_FILENO, &raw);
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}