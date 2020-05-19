/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** test_sigint_handler.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

static char *fill_output(char *output, char const *user, char const *host,
    int size)
{
    if (output != NULL) {
        my_memset(output, '\0', size + 1);
        my_strcat(my_strcat(my_strcat(output, "\n["), user), "@");
        my_strcat(my_strcat(output, host), " /]$ ");
    }
    return (output);
}

static char *get_print_output(char * const *envp)
{
    char *user = get_var_value(envp, find_var_env(envp, "USER"));
    char *host = get_var_value(envp, find_var_env(envp, "HOSTNAME"));
    char *output = NULL;
    int dot = my_strchr_index(host, '.');
    int size_host = (dot > 0) ? dot : my_strlen(host);
    char hostname[size_host + 1];
    int size = 1;

    if (user == NULL || host == NULL)
        return (NULL);
    chdir("/");
    my_strncpy(hostname, host, size_host);
    size += my_strlen(user);
    size += size_host;
    size += my_strlen("[@ /]$ ");
    output = malloc(sizeof(char) * (size + 1));
    return (fill_output(output, user, hostname, size));
}

Test(sigint_handler_for_prompt, print_again_the_prompt_when_sigint_is_raised)
{
    char *output = NULL;
    char save_dir[4097];

    getcwd(save_dir, 4097);
    output = get_print_output(DEFAULT_ENVIRONMENT);
    cr_assert_not_null(output);
    cr_redirect_stdout();
    cr_expect_null(bind_sigint_signal(PROMPT));
    kill(getpid(), SIGINT);
    cr_expect_stdout_eq_str(output);
    chdir(save_dir);
    free(output);
}
