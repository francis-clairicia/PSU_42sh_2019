/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** node
*/

#ifndef NODE_H_
#define NODE_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct node_s
{
    struct node_s *next;
    struct node_s *prev;
    void (*freer)(void *);
} node_t;

void *add_node(node_t **head, const size_t size, void (*freer)(void *));

void free_node_list(node_t *node);

#define DCLL_ADD_NODE(head, size, freer) \
        (add_node((node_t **)head, size, (void *)freer))
#define DCLL_FREE_NODE_LIST(node) (free_node_list((node_t *)node))

#define DCLL_NEXT(node) (((node_t *)node)->next)
#define DCLL_PREV(node) (((node_t *)node)->prev)

#endif /* !NODE_H_ */