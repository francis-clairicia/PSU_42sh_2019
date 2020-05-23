/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_cd_builtin.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(cd_builtin_command, change_the_current_working_directory)
{
    char save_actual_dir[4097];
    char current_dir[4097];
    shell_t *shell = init_shell_struct(DEFAULT_ENVIRONMENT);

    cr_redirect_stderr();
    cr_assert_not_null(getcwd(save_actual_dir, 4097));
    cr_assert_not_null(shell);
    eval_exec_cmd("cd /", shell);
    cr_expect_str_eq(getcwd(current_dir, 4097), "/");
    cr_expect_str_eq(get_var_env(shell->envp, "OLDPWD"), save_actual_dir);
    chdir(save_actual_dir);
    eval_exec_cmd("cd unknown_dir", shell);
    cr_expect_stderr_eq_str("unknown_dir: No such file or directory.\n");
    destroy_shell_struct(shell);
}

Test(cd_builtin_command, move_to_home_path_when_no_args)
{
    char save_actual_dir[4097];
    char current_dir[4097];
    shell_t *shell = init_shell_struct(DEFAULT_ENVIRONMENT);
    char *home_path = NULL;

    cr_assert_not_null(getcwd(save_actual_dir, 4097));
    cr_assert_not_null(shell);
    cr_expect_eq(eval_exec_cmd("cd", shell), 0);
    home_path = get_var_env(shell->envp, "HOME");
    cr_expect_str_eq(getcwd(current_dir, 4097), home_path);
    cr_expect_str_eq(get_var_env(shell->envp, "OLDPWD"), save_actual_dir);
    destroy_shell_struct(shell);
    chdir(save_actual_dir);
}

Test(cd_builtin_command, print_error_when_too_many_arguments_are_given)
{
    shell_t *shell = init_shell_struct(DEFAULT_ENVIRONMENT);

    cr_redirect_stderr();
    cr_expect_eq(eval_exec_cmd("cd / ~/Downloads", shell), -1);
    cr_expect_stderr_eq_str("cd: Too many arguments.\n");
    destroy_shell_struct(shell);
}

Test(cd_builtin_command, handle_null_value)
{
    shell_t *shell = NULL;

    cr_expect_eq(eval_exec_cmd("cd", NULL), -1);
    cr_expect_eq(eval_exec_cmd("cd", shell), -1);
}

Test(cd_builtin_command, handle_invalid_or_non_existing_home_folder)
{
    shell_t *shell = init_shell_struct(NULL);

    cr_redirect_stderr();
    cr_expect_eq(eval_exec_cmd("cd", shell), -1);
    eval_exec_cmd("setenv HOME unknown_dir", shell);
    cr_expect_eq(eval_exec_cmd("cd", shell), -1);
    cr_expect_stderr_eq_str("unknown_dir: No such file or directory.\n");
    destroy_shell_struct(shell);
}