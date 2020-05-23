/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** pop_dcll
*/

#include "dcll.h"

void pop_dcll(dcll_t **head)
{
    dcll_t *first = NULL;

    if (!head)
        return;
    first = *head;
    if (!first)
        return;
    first->next->prev = first->prev;
    first->prev->next = first->next;
    *head = first->next;
    if (first->freer)
        first->freer(first);
    free(first);
}