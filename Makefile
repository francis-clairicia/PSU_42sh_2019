##
## EPITECH PROJECT, 2020
## Makefile 42sh
## File description:
## Makefile used to compile the 42sh program.
##

SRC_MAIN			=	src/main.c														\
						src/mysh.c														\

SRC_CORE 			=	src/print_command_prompt.c										\
						src/sigint_handler.c											\

SRC_AUTO_COMPLETION	=	src/auto_completion/find_completion.c							\
						src/auto_completion/free_completion.c							\

SRC_BUILTIN			=	src/builtin/builtin_functions.c									\
						src/builtin/alias.c												\
						src/builtin/cd.c												\
						src/builtin/echo.c												\
						src/builtin/env.c												\
						src/builtin/exit.c												\
						src/builtin/fg.c												\
						src/builtin/setenv.c											\
						src/builtin/unalias.c											\
						src/builtin/unsetenv.c											\

SRC_DCLL			=	src/dcll/add_dcll.c												\
						src/dcll/dequeue_dcll.c											\
						src/dcll/free_dcll.c											\
						src/dcll/pop_dcll.c												\
						src/dcll/rotate_dcll.c											\

SRC_ENV				=	src/env_handlers/create_variable.c								\
						src/env_handlers/find_var_env.c									\
						src/env_handlers/get_var_value.c								\

SRC_ERROR			=	src/error_handlers/error.c										\

SRC_EXEC			=	src/exec_handlers/eval_exec_cmd.c								\
						src/exec_handlers/exec_piped_commands.c							\
						src/exec_handlers/exec_shell_commands.c							\

SRC_FILE			=	src/file_handlers/find_binary_in_path.c							\
						src/file_handlers/get_path_to_executable.c						\

SRC_JOB				=	src/job_control/check_process.c									\
						src/job_control/process.c										\

SRC_PARSE_INPUT		=	src/parse_input/commands/change_fd.c							\
						src/parse_input/commands/command_struct.c						\
						src/parse_input/commands/parse_cmd_list.c						\
						src/parse_input/file_handling/split_info_from_str.c				\
						src/parse_input/get_arguments/check_and_apply_redir.c			\
						src/parse_input/get_arguments/check_for_parse_elem.c			\
						src/parse_input/get_arguments/get_enums.c						\
						src/parse_input/get_arguments/get_magic_quotes.c				\
						src/parse_input/get_arguments/get_quoted_arg.c					\
						src/parse_input/get_arguments/get_redirection.c					\
						src/parse_input/get_arguments/get_splitter.c					\
						src/parse_input/get_arguments/get_unquoted_arg.c				\
						src/parse_input/get_arguments/parse_input.c						\
						src/parse_input/list_handling/add_nodes_to_list.c				\
						src/parse_input/list_handling/free_arguments.c					\
						src/parse_input/list_handling/free_parsed_input.c				\
						src/parse_input/list_handling/get_array_from_arg_list.c			\
						src/parse_input/list_handling/remove_nodes_from_list.c			\
						src/parse_input/unmatched_handling/check_unmatched_chars.c		\
						src/parse_input/magic_quote_handling/get_args_from_output.c		\
						src/parse_input/variable_handling/add_var_to_var_list.c			\
						src/parse_input/variable_handling/apply_vars_to_last_elem.c		\
						src/parse_input/variable_handling/free_var_list.c				\
						src/parse_input/variable_handling/get_var_in_var_list.c			\
						src/parse_input/variable_handling/remove_var_from_var_list.c	\
						src/parse_input/variable_handling/replace_var_call_by_var.c		\
						src/parse_input/variable_handling/show_var_list.c				\
						src/parse_input/wildcards_handling/add_args_for_matching.c		\
						src/parse_input/wildcards_handling/alter_parse_by_wildcards.c	\

SRC_SHELL			=	src/shell_struct/init_shell.c									\
						src/shell_struct/destroy_shell.c								\
						src/shell_struct/default_variables/path.c						\

SRC_TERM_DRIVER		=	src/terminal_driver/control_line/arrows/down.c					\
						src/terminal_driver/control_line/arrows/left.c					\
						src/terminal_driver/control_line/arrows/right.c					\
						src/terminal_driver/control_line/arrows/up.c					\
						src/terminal_driver/control_line/ctrl/backspace.c				\
						src/terminal_driver/control_line/ctrl/c.c						\
						src/terminal_driver/control_line/ctrl/d.c						\
						src/terminal_driver/control_line/ctrl/q.c						\
						src/terminal_driver/control_line/single_keys/backspace.c		\
						src/terminal_driver/control_line/reset_line.c					\
						src/terminal_driver/control_line/shift_line.c					\
						src/terminal_driver/control_line/single_keys/enter.c			\
						src/terminal_driver/init/init_term_driver.c						\
						src/terminal_driver/process/process_keys.c						\
						src/terminal_driver/die.c										\
						src/terminal_driver/get_term_line.c								\

SRC					=	$(SRC_CORE)														\
						$(SRC_AUTO_COMPLETION)											\
						$(SRC_BUILTIN)													\
						$(SRC_DCLL)														\
						$(SRC_ENV)														\
						$(SRC_ERROR)													\
						$(SRC_EXEC)														\
						$(SRC_FILE)														\
						$(SRC_JOB)														\
						$(SRC_PARSE_INPUT)												\
						$(SRC_SHELL)													\
						$(SRC_TERM_DRIVER)

CFLAGS				=	-Wall -Wextra

CPPFLAGS			=	-I./include -I./include/lib -I./include/mysh -I./include/terminal_driver

override LDFLAGS	+=	-L./lib

override LDLIBS		+=	-lmy

OBJ					=	$(SRC:.c=.o) $(SRC_MAIN:.c=.o)

NAME				=	42sh

all:	$(NAME)

$(NAME):	CFLAGS += -O2
$(NAME):	$(LDLIBS) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

-lmy:
	$(MAKE) -s -C ./lib/my

tests_run:	CFLAGS += --coverage
tests_run:	LDLIBS += -lcriterion
tests_run:	$(LDLIBS)
	@find -name "*.gc*" -delete
	$(CC) -o unit_tests $(SRC) tests/*.c $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)
	./unit_tests
	$(RM) unit_tests test*.gc*
	mkdir -p coverage
	mv *.gc* coverage/

coverage:
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches

debug:	CFLAGS += -g
debug:	$(LDLIBS)
	$(CC) -o $(NAME) $(SRC) $(SRC_MAIN) $(LDFLAGS) $(LDLIBS) $(CFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) unit_tests *.gc*

fclean:	clean
	$(RM) $(NAME)
	$(RM) debug
	$(MAKE) $@ -C ./lib/my

re:	fclean all

.PHONY:	all -lmy tests_run coverage debug clean fclean re
