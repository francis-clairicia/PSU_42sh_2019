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

//////////////////////////////////////////////////////////////////

//Global default macro for parsing enums.//
//-> Set enum to start with 1 instead of default 0.
#define NONE (0)
///////////////////////////////////////////

//////////////////////////////////////////////////////////////////

//////////////////////////////
//  Parsing Error Handling  //
//////////////////////////////

typedef enum mysh_parsing_error_s {
    MISSING_NAME_FOR_REDIRECT = 1,
    AMBIGUOUS_INPUT_REDIRECT,
    AMBIGUOUS_OUTPUT_REDIRECT,
    INVALID_NULL_COMMAND,
    ILLEGAL_VARIABLE_NAME,
    UNDEFINED_VARIABLE,
    UNMATCHED_SINGLE,
    UNMATCHED_DOUBLE,
    UNMATCHED_MAGIC,
} parse_error_t;

static const char *mysh_parse_error_str[] = {
    "Missing name for redirect.\n",
    "Ambiguous input redirect.\n",
    "Ambiguous output redirect.\n",
    "Invalid null command.\n",
    "Illegal variable name.\n",
    "Undefined variable.\n",
    "Unmatched '''.\n",
    "Unmatched '\"'.\n",
    "Unmatched '`'.\n",
};

////////////////////////////////////////////////////////////////
#define PARSE_ERROR_STR(error) (mysh_parse_error_str[error - 1])
////////////////////////////////////////////////////////////////

static inline void print_parsing_error(const parse_error_t error)
{
    if (error != NONE) {
        my_putstr_error(PARSE_ERROR_STR(error));
    }
};

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////

//////////////////////
//   Redirections   //
//////////////////////

//Redirections Input Characters Enum.
//
//PIPE                     -> 00000000 00000000 00000000 00000001 '|'
//APPEND_TO_FILE           -> 00000000 00000000 00000000 00000010 '>>'
//REDIR_IN_FILE            -> 00000000 00000000 00000000 00000100 '>'
//READ_FROM_STDIN_AS_INPUT -> 00000000 00000000 00000000 00001000 '<<'
//READ_FROM_FILE_AS_INPUT  -> 00000000 00000000 00000000 00010000 '<'
typedef enum redirection_type {
    PIPE = 1,
    APPEND_TO_FILE = 1 << 1,
    REDIR_IN_FILE = 1 << 2,
    READ_FROM_STDIN_AS_INPUT = 1 << 3,
    READ_FROM_FILE_AS_INPUT = 1 << 4,
} redirection_type_t;

////////////////////////////////////////////////////////////////
// -> Small Functions for ease to work with redirection enums //
////////////////////////////////////////////////////////////////

//Given a redirection_type_t enum, returns if it matches with an input type.
static inline bool is_input(const redirection_type_t redir)
{
    return (redir & (READ_FROM_STDIN_AS_INPUT | READ_FROM_FILE_AS_INPUT));
}

#define IS_INPUT(var) is_input((redirection_type_t)var)
////////////////////////////////////////////////////////////////

//Given a redirection_type_t enum, returns if it matches with an output type.
static inline bool is_output(const redirection_type_t redir)
{
    return (redir & (PIPE | APPEND_TO_FILE | REDIR_IN_FILE));
}

#define IS_OUTPUT(var) is_output((redirection_type_t)var)
////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

///////////////////
//   Splitters   //
///////////////////

//Splitters Input Characters Enum.
//
//SEMI_COLUMN -> ';'
//AND         -> '&&'
//OR          -> '||'
//BG          -> '&'
typedef enum splitter_type {
    SEMI_COLUMN = 1,
    AND,
    OR,
    BG,
} splitter_type_t;

/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
//   Const Strings and Arrays of Special Characters   //
////////////////////////////////////////////////////////

/////////////////////
// -> Redirections //
/////////////////////

static const char fc_redirections[] = "|><";

static const char * const redirections[] = {
    "|",
    ">>",
    ">",
    "<<",
    "<",
    NULL
};

//A Redirection Character is a character that implies either
//the input or the output of a command to be redirected.

#define FIRST_CHAR_REDIRECTION (fc_redirections)
#define REDIRECTIONS_ARRAY (redirections)

//////////////////
// -> Splitters //
//////////////////

static const char fc_splitters[] = ";&|";

static const char * const splitters[] = {
    ";",
    "&&",
    "||",
    "&",
    NULL
};

#define FIRST_CHAR_SPLITTER (fc_splitters)
#define SPLITTERS_ARRAY (splitters)


static const char spaces[] = " \t";
#define SPACES (spaces)

static const char arg_quotes[] = "\"'";
#define ARGUMENT_QUOTES (arg_quotes)

#define MAGIC_QUOTE_CHAR ('`')

//First characters of:
//
//SPACES + ARGUMENT_QUOTES + MAGIC_QUOTE_CHAR + SPLITTERS + REDIRECTIONS
static const char fc_stoppers[] = " \t\"'`;&|><";
#define FIRST_CHAR_STOPPER (fc_stoppers)

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
// -> Small Functions for ease to work with special characters //
/////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////

static inline bool loop_while_spaces(const char *input, size_t *i)
{
    return (my_loop_in_str_while_list_c(input, SPACES, i));
}

#define LOOP_SPACES(input, address_of_index) \
            (loop_while_spaces(input, address_of_index))
//////////////////////////////////////////////////////////

static inline bool is_char_spaces(const char c)
{
    return (my_is_char_in_str(SPACES, c));
}

#define IS_CHAR_SPACES(c) (is_char_spaces(c))
//////////////////////////////////////////////////////////

static inline char is_char_arg_quote(const char c)
{
    char match = '\0';
    size_t i = 0;

    for (; match == '\0' && ARGUMENT_QUOTES[i]; i += 1) {
        if (c == ARGUMENT_QUOTES[i])
            match = c;
    }
    return (match);
}

#define IS_CHAR_ARGUMENT_QUOTES(c) (is_char_arg_quote(c))
//////////////////////////////////////////////////////////

static inline bool is_char_splitter(const char c)
{
    return (my_is_char_in_str(FIRST_CHAR_SPLITTER, c));
}

#define IS_CHAR_SPLITTER(c) (is_char_splitter(c))
//////////////////////////////////////////////////////////

static inline bool is_char_redirection(const char c)
{
    return (my_is_char_in_str(FIRST_CHAR_REDIRECTION, c));
}

#define IS_CHAR_REDIRECTION(c) (is_char_redirection(c))
//////////////////////////////////////////////////////////

static inline bool is_char_stopper(const char c)
{
    return (my_is_char_in_str(FIRST_CHAR_STOPPER, c));
}

#define IS_CHAR_STOPPER(c) (is_char_stopper(c))
//////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

////////////////////
//  Parsing List  //
////////////////////

//Similar to a character array (char **) -> Contains each argument of a command.
typedef struct arguments {
    char *arg;
    struct arguments *next;
    struct arguments *prev;
} arguments_t;

//Contains all of the commands splitted by a splitter,
//binded through redirections or not.
//
//Special case: if redir_output_type is PIPE :
//    -> redir_output is NULL and opens a pipe()
//       in the execution part of the project.
typedef struct command_list {
    arguments_t *args;
    char *redir_input;
    redirection_type_t redir_input_type;
    char *redir_output;
    redirection_type_t redir_output_type;
    struct command_list *next;
    struct command_list *prev;
} cmd_list_t;

//Each node is made by splitting the input with splitters.
typedef struct parse_list {
    cmd_list_t *cmd_list;
    splitter_type_t splitter;
    struct parse_list *next;
    struct parse_list *prev;
} parse_list_t;

//////////////////////////////////

////////////////////////////////////////////////////////
//Reminders applied on last_quotation in indicator_t.
//-> Applies to remember the last parsed element nature.

#define WAS_UNQUOTED (1)
#define WAS_SINGLE (2)
#define WAS_DOUBLE (3)
#define WAS_MAGIC (4)

////////////////////////////////////////////////////////

//Index structure to move during the parsing process.
typedef struct indicator_s {
    const char *input;
    size_t i;
    bool separator;
    size_t last_quotation;
} indicator_t;

//////////////////////////////////

//Checks and prints if need if a matching quotation error is within cmd.
//
//Returns True (1) if not.
//Returns False (0) otherwise.
bool check_unmatched_chars(const char *cmd, parse_error_t *error);

/////////////////////////////////////////////////////////////////////////

/////////////////////////
//  PARSING FUNCTIONS  //
/////////////////////////

///////////////////////
#include "mysh_shell.h"
///////////////////////

// Parses an input into a parse_list_t *list.
parse_list_t *parse_input(shell_t *shell, const char *input,
                            parse_error_t *error);

// ADD NODES TO LISTS //

// Adds an argument node to an argument list.
void add_arg_list_node(arguments_t **list);

// Adds an argument node to an argument list after a previous node.
//
// Returns its address.
arguments_t *add_arg_list_node_index(arguments_t **list, arguments_t *previous);

// Adds a cmd_node to a cmd_list.
void add_cmd_list_node(cmd_list_t **list);

// Adds a parsed_list_node to a parsed_list.
void add_parsed_list_node(parse_list_t **list);

/////////////////////////

// RM NODES FROM LISTS //

// Removed an argument node from an argument list.
//
// Returns if it was removed.
bool remove_node_from_arg_list_index(arguments_t **list, arguments_t *to_rm);

/////////////////////////

// FUNCTION LIKE METHODS FOR LISTS //

// Makes an array from argument list
char **get_array_from_arg_list(arguments_t *arg_list);

/////////////////////////////////////

// LISTS / NODES FREERS //

// Frees a node from an arg list.
void free_arg_node(arguments_t *node);

// Frees an arg list.
void free_args_list(arguments_t *head);

// Frees a parse list.
void free_parse_list(parse_list_t *head);

//////////////////////////

// ENUM RETURNS //

// Both file the given ptr to the adress of an int to the nb of characters
// to skip to shift away from the special characters.

//Returns the enum matching the next redirection in shifted_input.
redirection_type_t get_redirection_enum(const char *restrict shifted_input,
                                        int *size);

//Returns the enum matching the next splitter in shifted_input.
splitter_type_t get_splitter_enum(const char *restrict shifted_input,
                                    int *size);

/////////////////


// Gets Arguments and enums. //

//Gets a quoted arg, put it in a new-last node of the given cmd_list,
//if separator is false, otherwise, concatenates it to the last arg
//of the last element of cmd_list.
//
//Increases index to the new arg/splitter/space.
void get_quoted_arg(cmd_list_t **head, indicator_t *indic);

//Gets an unquoted arg, put it in a new-last node of the given cmd_list,
//if separator is false, otherwise, concatenates it to the last arg
//of the last element of cmd_list.
//
//Increases index to the new arg/splitter/space/end of input.
void get_unquoted_arg(cmd_list_t **head, indicator_t *indic);

//Gets a command between two magic quotes, and pipes the output
//to the next executed command's input.
//
//Increases index after the end of the magic quotes.
void get_magic_quotes(shell_t *shell, cmd_list_t **head, indicator_t *indic);

//Get argument from the output of a command which was in between magic quotes.
void get_args_from_output(arguments_t **args, char const *command_line,
                            shell_t *shell);

//Gets a splitter, adds a new-last node to the parsed_input list,
//sets it the newly-found splitter.
//
//Increases index to the new arg/splitter/space/end of input.
bool get_splitter(parse_list_t **head, indicator_t *indic,
                    parse_error_t *error);

//Gets a redirection, creates a new-last node in the given cmd_list,
//
//Increases index to the new arg/splitter/space/end of input.
void get_redirection(cmd_list_t **head, indicator_t *indic,
                    parse_error_t *error);

//Checks if a the current index can be a new quoted argument.
//
//Sets (*found_arg) to true if it wasn't and the argument was a
//quoted argument.
void check_for_quoted_elem(bool *found_arg, cmd_list_t **cur_cmd_list,
                            indicator_t *indic);

//Checks if a the current index can be a new unquoted argument.
//
//Sets (*found_arg) to true if it wasn't and the argument was a
//unquoted argument.
void check_for_unquoted_elem(bool *found_arg, cmd_list_t **cur_cmd_list,
                            indicator_t *indic);

//Checks if a the current index can be a new magic quoted cmd.
//
//Sets (*found_arg) to true if it wasn't and the argument was a
//magic quote cmd.
void check_for_magic_quotes(bool *found_arg, shell_t *shell,
                        cmd_list_t **cur_cmd_list, indicator_t *indic);

//Checks if a the current index can be a splitter.
//
//Sets (*found_arg) to true if it wasn't and the argument was a
//splitter.
void check_for_splitter_elem(bool *found_arg, parse_list_t **head,
                            indicator_t *indic, parse_error_t *error);

//Checks if a the current index can be a redirection.
//
//Sets (*found_arg) to true if it wasn't and the argument was a
//redirection.
void check_for_redirection_elem(bool *found_arg, cmd_list_t **cur_cmd_list,
                                indicator_t *indic, parse_error_t *error);

//Checks for MISSING_NAME_REDIRECT and INVALID_NULL_COMMAND errors.
void check_redir_file_set(const cmd_list_t *cur_cmd, parse_error_t *error,
                        const redirection_type_t redir_type,
                        const char cur_char);

//Sets redir_type enums and checks for AMBIGUOUS_(IN/OUT)PUT_REDIRECT.
void set_redir_type(cmd_list_t **head, parse_error_t *error,
                    const redirection_type_t redir_type);

/////////////////////////////////////////////////////

/////////////////////////
//  Globbing Functions //
/////////////////////////

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

/////////////////////////////////

//Contains Splitted information a file.
typedef struct file_extent_s {
    char *path;
    char *file;
} file_extent_t;

//Treated is a boolean to refer if the string (str) found any match.
typedef struct globbing_match_s {
    const char *str;
    bool treated;
} globbing_match_t;

//To compare the processed to globbing recognition node with the head
//of the argument list.
typedef struct argument_globber_s {
    arguments_t **head;
    arguments_t *cur_node;
} argument_globber_t;

/////////////////////////////////

/////////////////////////
#include "my_wildcards.h"
/////////////////////////

#define WILDCARDS_IN_STR(str) \
        (my_is_char_in_str(str, GLOBAL_WC) | my_is_char_in_str(str, SOLO_WC))

//Add args to the given arg list from a given string where
//add_args_for_matching() is going to try to find files from potential
//paths hidden into match_str to do so.
bool add_args_for_matching(arguments_t **head, arguments_t *tmp);

//Takes the last argument ever put into the current parse_list node
//and puts, if found, any matching file with a potential given path
//in the argument to the argument list.
void apply_wildcards_changes(parse_list_t *cur_node);

/////////////////////////////////////////////////////////

///////////////
// Variables //
///////////////

///////////////////////////
#include "mysh_variables.h"
///////////////////////////

static const char _variable_stoppers[] = "/ \t";
//'\0' should be in the string but can't for obvious reasons.

#define VAR_STOPPERS (_variable_stoppers)

//////////////////////////////////////////////////////////

static inline bool is_char_variable_stopper(const char c)
{
    return ((c == '\0') | (my_is_char_in_str(VAR_STOPPERS, c)));
}

#define IS_CHAR_VAR_STOPPER(c) (is_char_variable_stopper(c))
//////////////////////////////////////////////////////////

#define GET_SIZE_REPLACED(str, i, size_call, size_replace) \
                ((i + size_replace + (my_strlen(str) - i - size_call)))


//Checks for variables in the last element.
//
//On fail -> Doesn't do anything.
//On issue with variable formulation -> Sets error value.
//On success -> Changed called variable in input by their value in the env.
void apply_vars_to_last_elem(parse_list_t *current_node,
                            shell_t *shell, parse_error_t *error);

//Subfunction of apply_vars_to_last_elem().
//Given a variable call, for instance: "$PATH",
//Replaces its occurences by the given replace variable in the
//derefenced string.
//
//Returns True if success or couldn't find any call.
//Returns False if the realloc of (*str) fails.
bool replace_var_call_by_var(char **str, const char *var_call,
                            const char *var_replace);

//////////////////////////////////////////////////////////

#ifdef DCLL_H_

////////////////////////
// Inheritance Macros //
////////////////////////

//Gets, from a void *ptr, the address of the given nb_bytes
//from the start of the ptr.
#define GET_ELEM_BEGIN(ptr, bytes) \
        (*(size_t *)(ptr + bytes))

//Gets, from a void *ptr, the address of the given nb_bytes
//from the end of the ptr.
#define GET_ELEM_END(ptr, size_of_type, bytes) \
        (*(size_t *)(ptr + size_of_type - bytes))

//Directly giving, in parameters, a head and a type,
//Redirect to add_parsing_node with a (void **) cast and sizeof(type).
#define ADD_PARSE_NODE(head, type) \
        (add_parsing_node((void **)(head), sizeof(type)))

#endif

//////////////////////////////////////////////////////////

#endif /* MYSH_PARSER_H_ */
