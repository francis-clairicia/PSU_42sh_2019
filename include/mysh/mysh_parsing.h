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

//////////////////////////////

#define UNMATCHED_SINGLE (1)
#define UNMATCHED_DOUBLE (2)

//////////////////////////////

//Redirections Input Characters Comparisons.
typedef enum redirection_type {
    PIPE = 0b1,
    APPEND_TO_FILE = 0b10,
    REDIR_IN_FILE = 0b100,
    READ_FROM_STDIN_AS_INPUT = 0b1000,
    READ_FROM_FILE_AS_INPUT = 0b10000,
} redirection_type_t;

/////////////////////////////////////////////////////////////////////////////

#define IS_OUTPUT(var) (var & \
                        (APPEND_TO_FILE | REDIR_IN_FILE | PIPE))

#define IS_INPUT(var) (var & \
                        (READ_FROM_STDIN_AS_INPUT | READ_FROM_FILE_AS_INPUT))

/////////////////////////////////////////////////////////////////////////////

static const char first_chars_redirections[] = "|><";

static const char * const redirections[] = {
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

static const char * const splitters[] = {
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
    char *redir_input;
    redirection_type_t redir_input_type;
    char *redir_output;
    redirection_type_t redir_output_type;
    struct command_list *next;
    struct command_list *prev;
} cmd_list_t;

typedef struct parsed_input_list {
    cmd_list_t *cmd_list;
    bool in_bg;
    splitter_type_t splitter;
    struct parsed_input_list *next;
    struct parsed_input_list *prev;
} parsed_input_list_t;

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

static inline char is_char_backstick(const char c)
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
    UNMATCHED_BACKTICKS = -1,
    MISSING_NAME_FOR_REDIRECT = 1,
    AMBIGUOUS_INPUT_REDIRECT,
    AMBIGUOUS_OUTPUT_REDIRECT,
    INVALID_NULL_COMMAND,
} error_parse_t;

static const char *parsing_errors[] = {
    "Missing name for redirect.\n",
    "Ambiguous input redirect.\n",
    "Ambiguous output redirect.\n",
    "Invalid null command.\n"
};

/////////////////////////////////////////////////////////////////////////

static inline void print_parsing_error(const error_parse_t error)
{
    if (error <= 0)
        return;
    my_putstr_error(parsing_errors[error - 1]);
};

//Checks and prints if need if a matching quotation error is within cmd.
//
//Returns True (1) if not.
//Returns False (0) otherwise.
bool check_unmatched_backticks(const char *cmd, error_parse_t *error);

/////////////////////////////////////////////////////////////////////////


/*
** --> PARSING FUNCTIONS <--
*/

// Parses an input into a parsed_input_list_t *list.
parsed_input_list_t *parse_input(const char *input, error_parse_t *error);

/////////////////////////////////////////////////////////

// Adds an argument node to an argument list.
void add_arg_list_node(arguments_t **head);

arguments_t *add_arg_list_node_index(arguments_t **head,
                                    arguments_t *previous);

void remove_node_from_arg_list_index(arguments_t **head,
                                    arguments_t *to_rm);

// Adds a cmd_node to a cmd_list.
void add_cmd_list_node(cmd_list_t **head);

// Adds a parsed_list_node to a parsed_list.
void add_parsed_list_node(parsed_input_list_t **head);


/////////////////////////////////////////////////////////

// Directly giving, in parameters, a head and a type,
// Redirect to add_parsing_node with a (void **) cast and sizeof(type).
#define ADD_PARSE_NODE(head, type) \
        (add_parsing_node((void **)(head), sizeof(type)))

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
redirection_type_t get_redirection_enum(const char *restrict shifted_input,
                                        int *size);

//Returns the enum matching the next splitter in shifted_input.
splitter_type_t get_splitter_enum(const char *restrict shifted_input,
                                    int *size);

void free_parsed_input_list(parsed_input_list_t *head);
void free_args_list(arguments_t *head);
void free_arg_node(arguments_t *node);


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
bool get_splitter(parsed_input_list_t **head, error_parse_t *error,
                const char *input, size_t *i);

//Gets a redirection, creates a new-last node in the given cmd_list,
//
//
//Increases index to the new arg/splitter/space/end of input.
void get_redirection(cmd_list_t **head, error_parse_t *error,
                    const char *input, size_t *i);

// Make an array with argument list
char **get_array_from_arg_list(arguments_t *arg_list);

//////////////////////////////////////////
//         Globbing Functions           //
//////////////////////////////////////////
///////////////////////////////////////////////////

//Gets a path string from a given str.
//For instance:
//From str = "/bin/ls".
//Will return : "/bin/".
//
//Returns the newly allocated string if success.
//Returns NULL if str is NULL or no path was found.
char *get_path_from_str(const char *str);

//Gets a matching-use string from a given str.
//For instance:
//From str = "/dev/tty*".
//Will return : "tty*".
//
//Returns the newly allocated string if success.
//Returns NULL if str is NULL or no path was found.
char *get_matching_from_str(const char *str);

///////////////////////////////////////////////////

/////////////////////////////////////////////////////////

typedef struct file_extent_s {
    char *path;
    char *file;
} file_extent_t;

typedef struct globbing_match_s {
    const char *str;
    bool treated;
} globbing_match_t;

typedef struct argument_globber_s {
    arguments_t **head;
    arguments_t *cur_node;
} argument_globber_t;

/////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////

#define WILDCARDS_IN_STR(str) (my_is_char_in_str(str, '*') \
                                || my_is_char_in_str(str, '?'))

///////////////////////////////////////////////////////////////////

//Add args to the given arg list from a given string where
//add_args_for_matching() is going to try to find files from potential
//paths hidden into match_str to do so.
bool add_args_for_matching(arguments_t **head, arguments_t *tmp,
                            const char *match_str);

void check_redir_file_set(const cmd_list_t *cur_cmd,
                        error_parse_t *error,
                        const redirection_type_t redir_type,
                        const char cur_char);

void set_redir_type(cmd_list_t **head, error_parse_t *error,
                    const redirection_type_t redir_type);

/////////////////////////////////////////////////////////

#endif /* MYSH_PARSER_H_ */
