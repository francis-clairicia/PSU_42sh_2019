/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Frees the parsed input nodes and lists.
*/

#include <stdlib.h>
#include "mysh_parsing.h"

void free_argument(arguments_t *dcll)
{
    if (!dcll)
        return;
    if (dcll->arg) {
        free(dcll->arg);
    }
}

void free_cmd(cmd_list_t *dcll)
{
    if (!dcll)
        return;
    if (dcll->args) {
        DCLL_FREE_LIST(dcll->args);
    }
    if (dcll->redir_name) {
        free(dcll->redir_name);
    }
}

void free_parsed_input(parsed_input_list_t *dcll)
{
    if (!dcll)
        return;
    if (dcll->cmd_list) {
        DCLL_FREE_LIST(dcll->cmd_list);
    }
}