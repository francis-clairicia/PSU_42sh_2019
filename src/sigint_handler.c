/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** sigint_handler.c
*/

#include "minishell.h"

void sigint_handler_for_prompt(int signum UNUSED)
{
    char current_directory[4097];

    my_putstr("\n");
    print_command_prompt(getcwd(current_directory, 4097), DEFAULT_ENVIRONMENT);
}

void sigint_handler_for_process(int signum UNUSED)
{
    return;
}

sighandler_t bind_sigint_signal(int func)
{
    sighandler_t sigint_handler[] = {
        sigint_handler_for_prompt,
        sigint_handler_for_process
    };

    return (signal(SIGINT, sigint_handler[func]));
}