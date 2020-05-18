/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** dcll
*/

#ifndef DCLL_H_
#define DCLL_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct dcll_s
{
    struct dcll_s *next;
    struct dcll_s *prev;
    void (*freer)(void *);
} dcll_t;

void *add_dcll(dcll_t **head, const size_t size, void (*freer)(void *));

void free_dcll_list(dcll_t *dcll);

#define DCLL_ADD(head, size, freer) \
        (add_dcll((dcll_t **)head, size, (void *)freer))
#define DCLL_FREE_LIST(dcll) (free_dcll_list((dcll_t *)dcll))

#define DCLL_NEXT(dcll) (((dcll_t *)dcll)->next)
#define DCLL_PREV(dcll) (((dcll_t *)dcll)->prev)

#define DCLL_NEXT_C(dcll, type) ((type)(((dcll_t *)dcll)->next))
#define DCLL_PREV_C(dcll, type) ((type)(((dcll_t *)dcll)->prev))

#endif /* !DCLL_H_ */