##
## EPITECH PROJECT, 2020
## Makefile 42sh
## File description:
## Makefile used to compile the 42sh program.
##

SRC_MAIN			=	src/main.c											\

SRC_MY_SH			=	src/mysh.c											\

SRC_ROOT			=	src/minishell.c										\
						src/shell.c											\
						src/exec_shell_commands.c							\
						src/exec_piped_commands.c							\
						src/print_command_prompt.c							\
						src/get_path_to_executable.c						\
						src/find_binary_in_path.c							\
						src/find_var_env.c									\
						src/get_var_value.c									\
						src/create_variable.c								\
						src/error.c											\
						src/sigint_handler.c								\

SRC_BUILTINS		=	src/builtin_functions.c								\
						src/builtin/cd.c									\
						src/builtin/env.c									\
						src/builtin/exit.c									\
						src/builtin/setenv.c								\
						src/builtin/unsetenv.c								\
						src/builtin/alias.c									\
						src/builtin/unalias.c								\

SRC_ENV				=	src/environment/add_new_env_var.c					\
						src/environment/create_array_from_env_list.c		\
						src/environment/create_env_list_from_array.c		\
						src/environment/free_env_list.c						\
						src/environment/get_env_list_size.c					\
						src/environment/get_var_in_env_list.c				\
						src/environment/remove_env_var.c					\
						src/environment/show_env.c							\

SRC_PARSE_INPUT		=	src/parse_input/parse_input.c						\
						src/parse_input/get_enums.c							\
						src/parse_input/free_parsed_input.c					\
						src/parse_input/add_nodes_to_list.c					\
						src/parse_input/get_arguments/get_quoted_arg.c		\
						src/parse_input/get_arguments/get_unquoted_arg.c	\
						src/parse_input/get_arguments/get_splitter.c		\
						src/parse_input/get_arguments/get_redirection.c		\
						src/parse_input/commands/parse_cmd_list.c			\
						src/parse_input/commands/command_struct.c			\
						src/parse_input/commands/change_fd.c				\

SRC_TERMINAL_DRIVER	=	src/terminal_driver/control_line/arrow_keys.c		\
						src/terminal_driver/control_line/shift_line.c		\
						src/terminal_driver/control_line/special_keys.c		\
						src/terminal_driver/init/init_term_driver.c			\
						src/terminal_driver/process/process_keys.c			\
						src/terminal_driver/die.c							\
						src/terminal_driver/get_term_line.c					\

SRC					=	$(SRC_MY_SH) $(SRC_ROOT) $(SRC_BUILTINS) $(SRC_ENV) $(SRC_PARSE_INPUT) $(SRC_TERMINAL_DRIVER)

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
	-./unit_tests
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

re:	fclean all

.PHONY:	all -lmy tests_run coverage debug clean fclean re
