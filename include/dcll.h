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

//Adds new node to given list
//New node is allocated and filled with the given freer
void *add_dcll(dcll_t **head, const size_t size, void (*freer)(void *));

//Deletes all node from given lits
//All nodes are free'd and found freeer are used on nodes
void free_dcll_list(dcll_t *dcll);

//Removes first node from given list
//Frees the first node and use it's freer if not NULL
void pop_dcll(dcll_t **head);

//Remove last node from given list
//Frees the last node and use it's freer if not NULL
void dequeue_dcll(dcll_t **head);

//Rotates the given list by moving the head to the adjacent node
void rotate_left_dcll(dcll_t **head);
void rotate_right_dcll(dcll_t **head);

#define DCLL_ADD(head, size, freer) \
        (add_dcll((dcll_t **)head, size, (void *)freer))
#define DCLL_FREE_LIST(dcll) (free_dcll_list((dcll_t *)dcll))

#define DCLL_DEQUEUE(dcll) (dequeue_dcll((dcll_t **)dcll))
#define DCLL_POP(dcll) (pop_dcll((dcll_t **)dcll))

#define DCLL_LEFT(dcll) (roate_left_dcll((dcll_t **)dcll))
#define DCLL_RIGHT(dcll) (roate_right_dcll((dcll_t **)dcll))

#define DCLL_NEXT(dcll) (((dcll_t *)dcll)->next)
#define DCLL_PREV(dcll) (((dcll_t *)dcll)->prev)

#define DCLL_NEXT_C(dcll, type) ((type)(((dcll_t *)dcll)->next))
#define DCLL_PREV_C(dcll, type) ((type)(((dcll_t *)dcll)->prev))

#endif /* !DCLL_H_ */