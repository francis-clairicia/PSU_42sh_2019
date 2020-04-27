/*
** EPITECH PROJECT, 2019
** 42sh
** File description:
** Parsing Header.
*/

#ifndef MYSH_PARSER_H_
#define MYSH_PARSER_H_

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
static const char backticks[] = "\"'";

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

static inline char is_char_backtick(const char c)
{
    char match = '\0';
    size_t i = 0;

    for (; match == '\0' && backticks[i]; i += 1) {
        if (c == backticks[i])
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


parsed_input_list_t *parse_input(const char *input, error_parse_t *error);

void add_node_to_arg_list(arguments_t **head);
void add_node_to_cmd_list(cmd_list_t **head);
void add_node_to_parsed_list(parsed_input_list_t **head);

ssize_t get_redirection_enum(const char *restrict shifted_input);
ssize_t get_splitter_enum(const char *restrict shifted_input);

void free_parsed_input_node(parsed_input_list_t *node);
void free_parsed_input_list(parsed_input_list_t *head);

void get_quoted_arg(cmd_list_t **head, const bool separator,
                        const char *input, size_t *i);
void get_unquoted_arg(cmd_list_t **head, const bool separator,
                    const char *input, size_t *i);
bool get_splitter(parsed_input_list_t **head, const char *input, size_t *i);
void get_redirection(cmd_list_t **head, error_parse_t *error,
                    const char *input, size_t *i);

#endif /* MYSH_PARSER_H_ */
