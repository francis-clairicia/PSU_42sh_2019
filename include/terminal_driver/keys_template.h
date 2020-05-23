/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** keys_template
*/

#ifndef KEYS_TEMPLATE_H_
#define KEYS_TEMPLATE_H_

#include "keys.h"

typedef struct key_template_s
{
    char key;
    int value;
} key_template_t;

static const key_template_t seq_template[] =
{
    {'A', ARROW_UP},
    {'B', ARROW_DOWN},
    {'C', ARROW_RIGHT},
    {'D', ARROW_LEFT},
    {'1', CTRL_ARROW_UP},
    {'2', CTRL_ARROW_DOWN},
    {'3', CTRL_ARROW_RIGHT},
    {'4', CTRL_ARROW_LEFT},
    {'H', HOME_KEY},
    {'F', END_KEY},
    {0, 0}
};

static const key_template_t ctrl_seq_template[] =
{
    {'A', CTRL_ARROW_UP},
    {'B', CTRL_ARROW_DOWN},
    {'C', CTRL_ARROW_RIGHT},
    {'D', CTRL_ARROW_LEFT},
    {0, 0}
};

//Translates the given char key into an corresponding enum
static inline int find_template_key(const key_template_t template[], char key)
{
    register size_t index = 0;

    if (!template)
        return ('\x1b');
    while (template[index].key && template[index].value) {
        if (template[index].key == key)
            return (template[index].value);
        index += 1;
    }
    return ('\x1b');
}

#endif /* !KEYS_TEMPLATE_H_ */