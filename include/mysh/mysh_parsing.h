/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** Parsing Header.
*/

#ifndef MYSH_PARSING_H_
#define MYSH_PARSING_H_

#include <stdbool.h>
#include <stddef.h>
#include "my.h"

#define NONE (0)

//Redirections Input Characters Comparisons.
typedef enum redirection_type {
    PIPE = 1,
    APPEND_TO_FILE = 2,
    REDIR_IN_FILE = 3,
    READ_FROM_STDIN_AS_INPUT = 4,
    READ_FROM_FILE_AS_INPUT = 5,
} redirection_type_t;

static const char first_chars_redirections[] = "|><";

static const char *redirections[] = {
    "|",
    ">>",
    ">",
    "<<",
    "<",
    NULL
};

//end -> Redirections

//Splitters Input Characters Comparisons.
typedef enum splitter_type {
    SEMI_COLUMN = 1,
    AND = 2,
    OR = 3
} splitter_type_t;

static const char first_chars_splitters[] = ";&|";

static const char *splitters[] = {
    ";",
    "&&",
    "||",
    NULL
};

//end -> Splitters

//Parsing Lists
typedef struct arguments {
    char *arg;
    struct arguments *next;
    struct arguments *prev;
} arguments_t;

typedef struct command_list {
    arguments_t *args;
    char *redir_name;
    redirection_type_t redir_type;
    struct command_list *next;
    struct command_list *prev;
} cmd_list_t;

typedef struct parsed_input_list {
    cmd_list_t *cmd_list;
    splitter_type_t splitter;
    struct parsed_input_list *next;
    struct parsed_input_list *prev;
} parsed_input_list_t;

//end -> Parsing list


static const char spaces[] = " \t";
static const char backsticks[] = "\"'";

static const char all_splitters[] = " \t\"';&|><";
static const char all_stoppers[] = ";&|><";


static inline bool is_char_spaces(const char c)
{
    return (my_is_char_in_str(spaces, c));
}

static inline bool loop_while_spaces(const char *input, size_t *i)
{
    return (my_loop_in_str_while_list_c(input, spaces, i));
}

static inline bool is_char_splitter(const char c)
{
    return (my_is_char_in_str(first_chars_splitters, c));
}

static inline bool is_char_redirection(const char c)
{
    return (my_is_char_in_str(first_chars_redirections, c));
}

static inline char is_char_backstick(const char c)
{
    char match = '\0';
    size_t i = 0;

    for (; match == '\0' && backsticks[i]; i += 1) {
        if (c == backsticks[i])
            match = c;
    }
    return (match);
}

static inline bool is_char_stopper(const char c)
{
    return (my_is_char_in_str(all_stoppers, c));
}

typedef enum error_parse {
    MISSING_NAME_FOR_REDIRECT = 1,
    AMBIGUOUS_OUTPUT_REDIRECT = 2,
    INVALID_NULL_COMMAND = 3,
} error_parse_t;

static const char *parsing_errors[] = {
    "Missing name for redirect.\n",
    "Ambiguous output redirect.\n",
    "Invalid null command.\n"
};

static inline void print_parsing_error(const error_parse_t error)
{
    if (error <= 0)
        return;
    my_putstr(parsing_errors[error - 1]);
};


/*
** --> PARSING FUNCTIONS <--
*/

// Parses an input into a parsed_input_list_t *list.
parsed_input_list_t *parse_input(const char *input, error_parse_t *error);

/////////////////////////////////////////////////////////

// Adds a node to a doubly linked list.
void *add_parsing_node(void **head, const size_t size);

// Directly giving, in parameters, a head and a type,
// Redirect to add_parsing_node with a (void **) cast and sizeof(type).
#define ADD_PARSE_NODE(head, type) \
        (add_parsing_node((void **)head, sizeof(type)))

/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////

//Gets, from a void *ptr, the address of the given nb_bytes
//from the start of the ptr.
#define GET_ELEM_BEGIN(ptr, bytes) \
        (*(size_t *)(ptr + bytes))

//Gets, from a void *ptr, the address of the given nb_bytes
//from the end of the ptr.
#define GET_ELEM_END(ptr, size_of_type, bytes) \
        (*(size_t *)(ptr + size_of_type - bytes))

/////////////////////////////////////////////////////////

//Returns the enum matching the next redirection in shifted_input.
ssize_t get_redirection_enum(const char *restrict shifted_input);

//Returns the enum matching the next splitter in shifted_input.
ssize_t get_splitter_enum(const char *restrict shifted_input);

void free_parsed_input_node(parsed_input_list_t *node);
void free_parsed_input_list(parsed_input_list_t *head);


// Gets Arguments and enums.

//Gets a quoted arg, put it in a new-last node of the given cmd_list,
//if separator is false, otherwise, concatenates it to the last arg
//of the last element of cmd_list.
//
//Increases index to the new arg/splitter/space.
void get_quoted_arg(cmd_list_t **head, const bool separator,
                    const char *input, size_t *i);

//Gets an unquoted arg, put it in a new-last node of the given cmd_list,
//if separator is false, otherwise, concatenates it to the last arg
//of the last element of cmd_list.
//
//Increases index to the new arg/splitter/space/end of input.
void get_unquoted_arg(cmd_list_t **head, const bool separator,
                    const char *input, size_t *i);

//Gets a splitter, adds a new-last node to the parsed_input list,
//sets it the newly-found splitter.
//
//Increases index to the new arg/splitter/space/end of input.
bool get_splitter(parsed_input_list_t **head, const char *input, size_t *i);

//Gets a redirection, creates a new-last node in the given cmd_list,
//
//
//Increases index to the new arg/splitter/space/end of input.
void get_redirection(cmd_list_t **head, error_parse_t *error,
                    const char *input, size_t *i);

#endif /* MYSH_PARSER_H_ */
