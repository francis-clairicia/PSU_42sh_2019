##
## EPITECH PROJECT, 2020
## Makefile 42sh
## File description:
## Makefile used to compile the 42sh program.
##

SRC_NO_TEST			=	src/main.c											\
						src/mysh.c

SRC_TEST			=	src/minishell.c										\
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
						src/builtin_functions.c								\
						src/builtin/cd.c									\
						src/builtin/env.c									\
						src/builtin/exit.c									\
						src/builtin/setenv.c								\
						src/builtin/unsetenv.c								\
						src/parse_input/parse_input.c						\
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

SRC					=	$(SRC_NO_TEST) $(SRC_TEST)

CFLAGS				=	-Werror -Wextra

CPPFLAGS			=	-I./include/

override LDFLAGS	+=	-L./lib

override LDLIBS		+=	-lmy

OBJ					=	$(SRC:.c=.o)

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
	$(CC) -o unit_tests $(SRC_TEST) tests/*.c $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)
	-./unit_tests
	$(RM) unit_tests test*.gc*
	mkdir -p coverage
	mv *.gc* coverage/

debug:	CFLAGS += -g
debug:	$(LDLIBS)
	$(CC) -o $(NAME) $(SRC) $(LDFLAGS) $(LDLIBS) $(CFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) unit_tests *.gc*

fclean:	clean
	rm -f $(NAME)
	rm -f debug

re:	fclean all

.PHONY:	all -lmy tests_run debug clean fclean re
