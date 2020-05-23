/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** dequeue_dcll
*/

#include "dcll.h"

void dequeue_dcll(dcll_t **head)
{
    dcll_t *last = NULL;

    if (!head)
        return;
    last = (*head)->prev;
    if (!last)
        return;
    last->prev->next = *head;
    (*head)->prev = last->prev;
    if (last->freer)
        last->freer(last);
    free(last);
}