/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** rotate_dcll
*/

#include "dcll.h"

void rotate_left_dcll(dcll_t **head)
{
    if (!head || !(*head))
        return;
    *head = (*head)->prev;
}

void rotate_right_dcll(dcll_t **head)
{
    if (!head || !(*head))
        return;
    *head = (*head)->next;
}