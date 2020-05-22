/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2019
** File description:
** test_executable_path.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(get_path_to_executable, find_out_the_path_of_a_binary)
{
    char *path_list[] = {"/usr/bin", "/bin", NULL};
    char *path = get_path_to_executable("ls", path_list);
    char *path_2 = get_path_to_executable("/bin/ls", path_list);

    cr_assert_not_null(path);
    cr_assert_not_null(path_2);
    cr_expect(my_strcmp(path, "/usr/bin/ls") == 0
            || my_strcmp(path, "/bin/ls") == 0);
    cr_expect_str_eq(path_2, "/bin/ls");
    free(path);
    free(path_2);
}

Test(get_path_to_executable, print_error_when_command_not_found)
{
    char *path_list[] = {"/usr/bin", "/bin", NULL};
    char *path = NULL;
    char *path_2 = NULL;
    char expected[] = "unknown: Command not found.\n./p: Command not found.\n";

    cr_redirect_stderr();
    path = get_path_to_executable("unknown", path_list);
    path_2 = get_path_to_executable("./p", path_list);
    cr_assert_null(path);
    cr_assert_null(path_2);
    cr_assert_stderr_eq_str(expected);
}

Test(get_path_to_executable, print_error_when_permission_denied)
{
    char *path_list[] = {"/usr/bin", "/bin", NULL};
    char *path = NULL;

    cr_redirect_stderr();
    path = get_path_to_executable("./Makefile", path_list);
    cr_assert_null(path);
    cr_assert_stderr_eq_str("./Makefile: Permission denied.\n");
}

Test(get_path_to_executable, print_error_when_its_a_directory)
{
    char *path_list[] = {"/usr/bin", "/bin", NULL};
    char *path = NULL;

    cr_redirect_stderr();
    path = get_path_to_executable("./include/", path_list);
    cr_assert_null(path);
    cr_assert_stderr_eq_str("./include/: Permission denied.\n");
}