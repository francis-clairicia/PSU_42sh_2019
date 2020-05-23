/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** free_dcll
*/

#include "dcll.h"

void free_dcll_list(dcll_t *dcll)
{
    dcll_t *final = NULL;
    dcll_t *tmp = NULL;

    if (!dcll)
        return;
    final = dcll;
    tmp = dcll;
    do {
        dcll = dcll->next;
        if (tmp && tmp->freer)
            tmp->freer(tmp);
        if (tmp)
            free(tmp);
        tmp = dcll;
    } while (tmp != final);
}