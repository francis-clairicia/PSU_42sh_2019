/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** mysh_env.h
*/

#ifndef MYSH_ENV_H_
#define MYSH_ENV_H_

#include <stdbool.h>

#define NO_MATCH (-1)
#define EXIT_MYSH (1)

typedef enum input_handling_e {
    NORMAL,
    RETURN,
    EOF_SENT,
    UNMATCHED_SINGLE,
    UNMATCHED_DOUBLE,
} input_handling_t;

//Doubly circular env list containing a variable
//name and value for each variable node.
//
//For instance, a variable set by Target=Sonic,
//would have the var_name set as: "Target",
//and its var_value set as: "Sonic".
typedef struct env_list_s {
    char *var_name;
    char *var_value;
    struct env_list_s *next;
    struct env_list_s *prev;
} env_list_t;

//Adds a new environment variable to the env_list.
//
//Returns True if success.
//Returns False if an error occured.
bool add_new_env_var(env_list_t **list,
                    const char *var_name, const char *var_value);

//Removes an environment variable from the env_list.
//
//Returns True if removed.
//Returns False if not found or an error occured.
bool remove_env_var(env_list_t **list, const char *var_name);

//Prints the env_list onto the stdout file descriptor in the format
//a classic shell would do.
void show_env(env_list_t *list);

//Gets the size of an env_list (number of nodes).
//
//Returns the size in a size_t.
//Returns 0 if the env_list ptr is NULL.
size_t get_env_list_size(env_list_t *list);

//Gets a pointer to the (first) variable that matches with the given
//variable name in env_list.
//
//Returns NULL if not found.
env_list_t *get_var_in_env_list(env_list_t *head, const char *var_name);

//Frees allocated memory in a given env_list node ptr checking if there's
//memory to be free'd.
void free_env_node(env_list_t *node);

//Frees allocated memory in a given env_list list ptr checking if there's
//memory to be free'd.
void free_env_list(env_list_t *list);

//From an env_list template, allocates and fills a char ** such as a
//classic env.
//
//Returns NULL if the given list is NULL or if malloc returned NULL.
char **create_array_from_env_list(env_list_t *list);

//From a char ** template, allocates and fills an env_list.
//
//Returns NULL if the given array is NULL or if malloc returned NULL.
env_list_t *create_env_list_from_array(const char * const *envg);

#endif /* MYSH_ENV_H_ */
