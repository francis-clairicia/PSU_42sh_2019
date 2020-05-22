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
    {'H', HOME_KEY},
    {'F', END_KEY},
    {0, 0}
};

//Translates the given char key into an corresponding enum
static inline int find_seq_key(char key)
{
    register size_t index = 0;

    while (seq_template[index].key && seq_template[index].value) {
        if (seq_template[index].key == key)
            return (seq_template[index].value);
        index += 1;
    }
    return ('\x1b');
}

#endif /* !KEYS_TEMPLATE_H_ */