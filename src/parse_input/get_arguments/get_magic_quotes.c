/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** get_magic_quotes.c
*/

#include "mysh_parsing.h"

void get_magic_quotes(shell_t *shell, cmd_list_t **head, indicator_t *indic)
{
    char *buffer_cmd = NULL;

    indic->i += 1;
    buffer_cmd = my_strdup_char_i(&indic->input[indic->i],
                                    MAGIC_QUOTE_CHAR, &indic->i);
    if (head && (*head))
        get_args_from_output(&(*head)->prev->args, buffer_cmd, shell);
    if (buffer_cmd)
        free(buffer_cmd);
    indic->i += 1;
    indic->last_quotation = WAS_MAGIC;
}