/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** keys
*/

#ifndef KEYS_H_
#define KEYS_H_

//Enum representing special characters
typedef enum keys_s
{
    BACKSPACE = 127,
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    CTRL_ARROW_LEFT,
    CTRL_ARROW_RIGHT,
    CTRL_ARROW_UP,
    CTRL_ARROW_DOWN,
    DEL_KEY,
    HOME_KEY,
    END_KEY,
    PAGE_UP,
    PAGE_DOWN
} keys_t;

#endif /* !KEYS_H_ */