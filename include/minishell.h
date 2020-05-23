/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** minishell.h
*/

#ifndef HEADER_MINI_SHELL
#define HEADER_MINI_SHELL

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "my.h"
#include "mylist.h"
#include "mysh_parsing.h"
#include "mysh_shell.h"

#define DEFAULT_ENVIRONMENT __environ

#ifndef WCOREDUMP
#define WCOREDUMP(wstatus) __WCOREDUMP(wstatus)
#endif

typedef struct command_line
{
    char **argv;
    int input_fd;
    int output_fd;
    int error_fd;
} command_t;

int mysh(void);
int eval_exec_cmd(char const *command_line, shell_t *shell);
int exec_shell_commands(command_t commands[], shell_t *shell);
int exec_piped_commands(cmd_list_t *cmd_list, shell_t *shell);
void print_command_prompt(char const *cwd, char * const *envp);
char *get_path_to_executable(char const *binary, char * const *path_list);
char *join_path(char const *path_1, char const *path_2);
char *find_binary_in_path(char const *binary, char * const *path_list);
int find_var_env(char * const *envp, char const *var);
char *get_var_value(char * const *envp, int index);
char *create_variable(char const *variable, char const *value);
#define get_var_env(envp, var) get_var_value(envp, find_var_env(envp, var))

command_t init_command_struct(void);
void destroy_command(command_t *command);
command_t *parse_cmd_list(cmd_list_t *cmd_list, int *nb_commands);
int get_input_fd(char const *file, redirection_type_t type);
int get_output_fd(char const *file, redirection_type_t type);

typedef int (*builtin_t)(char * const *av, shell_t *shell);

struct builtin
{
    char const *command;
    builtin_t function;
};

int launch_builtin(builtin_t builtin, command_t commands[], shell_t *shell);
builtin_t is_builtin(char * const *cmd);
int cd_builtin_command(char * const *av, shell_t *shell);
int env_builtin_command(char * const *av, shell_t *shell);
int exit_builtin_command(char * const *av, shell_t *shell);
int setenv_builtin_command(char * const *av, shell_t *shell);
int unsetenv_builtin_command( char * const *av, shell_t *shell);
int fg_builtin_command(char * const *av, shell_t *shell);
int alias_builtin_command(char * const *av, shell_t *shell);
int unalias_builtin_command(char * const *av, shell_t *shell);

#define print_env(shell) \
    env_builtin_command((char *[]){"env", NULL}, shell)
#define set_var_to_env(variable, value, shell) \
    setenv_builtin_command((char *[]){"setenv", \
    (char *)variable, (char *)value, NULL}, shell)
#define remove_var_from_env(variable, shell) \
    unsetenv_builtin_command((char *[]){"unsetenv", \
    (char *)variable, NULL}, shell)

void bind_sigint_signal(void);

void print_error(char const *filepath, char const *error);
void print_signal(int signum, int core_dump, bool end_line);
char *error_exec(int errnum);

#endif