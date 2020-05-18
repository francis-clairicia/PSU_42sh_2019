/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** add_dcll
*/

#include <string.h>
#include "dcll.h"

static void * add_first_dcll(dcll_t **head, dcll_t *new_dcll)
{
    if (!head || !new_dcll)
        return (NULL);
    new_dcll->next = new_dcll;
    new_dcll->prev = new_dcll;
    *head = new_dcll;
}

static void * add_new_dcll(dcll_t **head, dcll_t *new_dcll)
{
    if (!head || !new_dcll)
        return (NULL);
    new_dcll->next = (*head);
    new_dcll->prev = (*head)->prev;
    (*head)->prev->next = new_dcll;
    (*head)->prev = new_dcll;
    return (new_dcll);
}

void *add_dcll(dcll_t **head, const size_t size, void (*freer)(void *))
{
    dcll_t *new_dcll = NULL;

    if (!head || size < sizeof(dcll_t))
        return (NULL);
    new_dcll = malloc(size);
    if (!new_dcll)
        return (NULL);
    memset(new_dcll, 0, size);
    new_dcll->freer = freer;
    if (!(*head)) {
        return (add_first_dcll(head, new_dcll));
    } else {
        return (add_new_dcll(head, new_dcll));
    }
}