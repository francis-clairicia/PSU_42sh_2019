/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** Sets up the env_list and call mysh in a loop.
*/

#include <stddef.h>
#include "mysh_env.h"
#include "mysh_parsing.h"

int setup_mysh(const char * const env[])
{
    env_list_t *env_list = NULL;
    const char input[] = "ls \"-a\"|\t cat '-e' > 'txt'\"a\"";
    parsed_input_list_t *list = NULL;
    error_parse_t error = NONE;

    env_list = create_env_list_from_array(env);
    //while (mysh(&env_list));
    free_env_list(env_list);
    list = parse_input(input, &error);
    DCLL_FREE_LIST(list);
    return (0);
}