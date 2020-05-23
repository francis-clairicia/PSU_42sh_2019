/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** mysh.c
*/

#include "minishell.h"
#include "terminal_driver.h"

static void increase_shlvl(shell_t *shell)
{
    char *actual_value = get_var_env(shell->envp, "SHLVL");
    int new_value = my_getnbr(actual_value) + 1;
    char *str_value = NULL;

    if (actual_value == NULL)
        return;
    str_value = my_nbr_to_str(new_value);
    if (!str_value)
        return;
    set_var_to_env("SHLVL", str_value, shell);
    free(str_value);
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
    *line = get_term_line();
    if (!(*line))
        *line = my_strdup("exit");
    if (my_strlen(*line) == 0)
        return (command_prompt(line, 0));
    return (1);
}

static int launch_given_commands(shell_t *shell)
{
    char *cmd = NULL;
    int stop_shell = 0;

    while (stop_shell <= 0 && get_next_line_2(&cmd, 0))
        stop_shell = eval_exec_cmd(cmd, shell);
    if (cmd != NULL)
        free(cmd);
    destroy_shell_struct(shell);
    return (0);
}

int mysh(void)
{
    char *cmd = NULL;
    shell_t *shell = init_shell_struct(DEFAULT_ENVIRONMENT);
    int status = 0;
    int final_status = 0;

    if (shell == NULL)
        return (84);
    remove_var_from_env("OLDPWD", shell);
    if (!isatty(0))
        return (launch_given_commands(shell));
    atexit(disable_raw_mode);
    increase_shlvl(shell);
    while (command_prompt(&cmd, status)) {
        status = eval_exec_cmd(cmd, shell);
        check_background_process(shell);
    }
    final_status = shell->exit_status;
    destroy_shell_struct(shell);
    return (final_status);
}