/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** mysh_aliases.h
*/

#ifndef MYSH_ALIASES_H_
#define MYSH_ALIASES_H_

// Alias Struct
typedef struct alias_s {
    char *alias;
    char **cmd;
    struct alias_s *next;
} alias_t;
// end -> Alias Struct

void destroy_every_alias(alias_t **alias_list);

#endif