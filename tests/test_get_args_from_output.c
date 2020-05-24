/*
** EPITECH PROJECT, 2019
** PSU_42sh_2019
** File description:
** test_get_args_from_output.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "mysh_parsing.h"

Test(get_args_from_output, put_all_words_in_command_output_as_args)
{
    arguments_t *args = NULL;
    shell_t *shell = init_shell_struct(NULL);
    char *expected[] = {"Hello", "It's", "Me", "Again", NULL};
    char **array = NULL;

    get_args_from_output(&args, "echo \"Hello It's Me\"; echo Again", shell);
    cr_assert_not_null(args);
    array = get_array_from_arg_list(args);
    cr_expect_not_null(array);
    if (array) {
        cr_expect_eq(my_arrcmp(array, expected), 0);
        my_free_array(array);
    }
    free_args_list(args);
    destroy_shell_struct(shell);
}

Test(get_args_from_output, do_not_put_arg_with_exit)
{
    arguments_t *args = NULL;
    shell_t *shell = init_shell_struct(NULL);

    get_args_from_output(&args, "exit", shell);
    cr_expect_null(args);
    destroy_shell_struct(shell);
}

Test(get_args_from_output, do_not_put_arg_on_error)
{
    arguments_t *args = NULL;
    shell_t *shell = init_shell_struct(NULL);

    cr_redirect_stderr();
    get_args_from_output(&args, "ls the_unknown_file_or_dir", shell);
    cr_expect_null(args);
    cr_expect_stderr_eq_str("ls: cannot access 'the_unknown_file_or_dir': "
                            "No such file or directory\n");
    destroy_shell_struct(shell);
}