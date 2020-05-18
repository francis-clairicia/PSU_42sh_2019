/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** Creates an array from an env_list.
*/

#include <stdbool.h>
#include <stdlib.h>
#include "my.h"
#include "mysh_env.h"

static bool init_envg(char ***envg, const size_t size)
{
    register size_t index = 0;

    if (!size)
        return (false);
    *envg = malloc(sizeof(char *) * (size + 1));
    if (!(*envg))
        return (false);
    while (index < size) {
        (*envg)[index] = NULL;
        index += 1;
    }
    (*envg)[index] = NULL;
    return (true);
}

static bool assert_envg_line(char **envg_line, env_list_t *node)
{
    char *tmp = NULL;

    tmp = my_strcat(node->var_name, "=", false, false);
    if (!tmp)
        return (false);
    *envg_line = my_strcat(tmp, node->var_value, true, false);
    return (*envg_line) ? true : false;
}

char **create_array_from_env_list(env_list_t *head)
{
    register size_t index = 0;
    env_list_t *tmp = NULL;
    char **envg = NULL;
    size_t size = get_env_list_size(head);

    if (!init_envg(&envg, size))
        return (NULL);
    tmp = head;
    do {
        if (!assert_envg_line(&envg[index], tmp)) {
            my_free_array((void *)envg);
            return (NULL);
        }
        index += 1;
        tmp = tmp->next;
    } while (index < size && tmp != head->prev);
    return (envg);
}