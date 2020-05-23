/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** sigint_handler.c
*/

#include "minishell.h"

void sigint_handler_for_process(int signum UNUSED)
{
    return;
}

void bind_sigint_signal(void)
{
    signal(SIGINT, sigint_handler_for_process);
}