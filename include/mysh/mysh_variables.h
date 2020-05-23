/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** mysh_variables.h
*/

#ifndef MYSH_VARIABLES_H_
#define MYSH_VARIABLES_H_

#include <stdbool.h>

typedef struct var_list_s {
    char *var_name;
    char *var_value;
    struct var_list_s *next;
    struct var_list_s *prev;
} var_list_t;

bool add_var_to_var_list(var_list_t **var_list, const char *var_name,
                        const char *var_value);

bool remove_var_from_var_list(var_list_t **var_list, const char *var_name);

var_list_t *get_var_in_var_list(var_list_t *head, const char *var_name);

void free_var_node(var_list_t *node);
void free_var_list(var_list_t *var_list);

void show_var_list(var_list_t *head);

#endif /* MYSH_VARIABLES_H_ */