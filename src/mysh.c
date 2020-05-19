/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** mysh.c
*/

#include "minishell.h"

static void increase_shlvl(char ***envp)
{
    char *actual_value = get_var_value(*envp, find_var_env(*envp, "SHLVL"));
    int new_value = my_getnbr(actual_value) + 1;
    char *setenv_cmd[] = {"setenv", "SHLVL", NULL, NULL};

    if (actual_value == NULL)
        return;
    setenv_cmd[2] = my_nbr_to_str(new_value);
    setenv_builtin_command(setenv_cmd, envp);
    free(setenv_cmd[2]);
}

static int command_prompt(char **line, int stop_shell)
{
    char current_directory[4097];

    if (stop_shell == 1) {
        if (*line != NULL)
            free(*line);
        return (0);
    }
    bind_sigint_signal(PROMPT);
    print_command_prompt(getcwd(current_directory, 4097), DEFAULT_ENVIRONMENT);
    if (!get_next_line_2(line, 0))
        *line = my_strdup("exit");
    if (my_strlen(*line) == 0)
        return (command_prompt(line, 0));
    return (1);
}

static int launch_given_commands(char ***envp)
{
    char *cmd = NULL;
    int stop_shell = 0;

    while (stop_shell <= 0 && get_next_line_2(&cmd, 0))
        stop_shell = minishell(cmd, envp);
    if (cmd != NULL)
        free(cmd);
    my_free_array(*envp);
    return (0);
}

int mysh(void)
{
    char *cmd = NULL;
    char **envp = my_array_dup(DEFAULT_ENVIRONMENT);
    int stop_shell = 0;

    if (envp == NULL)
        return (84);
    unsetenv_builtin_command((char *[]){"unsetenv", "OLDPWD", NULL}, &envp);
    if (!isatty(0))
        return (launch_given_commands(&envp));
    increase_shlvl(&envp);
    while (command_prompt(&cmd, stop_shell))
        stop_shell = minishell(cmd, &envp);
    my_free_array(envp);
    return (0);
}