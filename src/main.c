/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** main.c
*/

#include "my.h"
#include "mysh.h"
#include "mysh_usage.h"

int mysh(void);

int main(const int ac, const char * const av[],
    const char * const env[] UNUSED)
{
    if (ac < 1 || !av || !av[0])
        return (84);
    if (ac != 1) {
        if (ac == 2 && my_mass_strcmp(av[1], "-h", "--help", NULL)) {
            my_printf(usage, av[0]);
            return (0);
        }
        return (84);
    }
    return (mysh());
}