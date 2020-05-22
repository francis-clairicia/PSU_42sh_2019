/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** error.c
*/

#include "minishell.h"

void print_error(char const *filepath, char const *error)
{
    my_dprintf(2, "%s: %s.\r\n", filepath, error);
}

char *error_exec(int errnum)
{
    if (errnum == ENOEXEC)
        return ("Exec format error. Wrong Architecture");
    return (strerror(errnum));
}

void print_signal(int signum, int core_dump, bool end_line)
{
    if (signum == SIGFPE)
        my_putstr_error("Floating exception");
    else
        my_putstr_error(strsignal(signum));
    if (core_dump)
        my_putstr_error(" (core dumped)");
    if (end_line)
        my_putstr_error("\n");
}