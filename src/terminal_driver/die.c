/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** die
*/

#include "terminal_driver.h"

void die(char *str)
{
    perror(str);
    exit(1);
}