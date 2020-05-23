/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** history
*/

#ifndef HISTORY_H_
#define HISTORY_H_

#include "dcll.h"

typedef struct history_s
{
    dcll_t dcll;
    char *line;
} history_s;

#endif /* !HISTORY_H_ */