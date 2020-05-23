##
## EPITECH PROJECT, 2020
## Makefile 42sh
## File description:
## Makefile used to compile the 42sh program.
##

SRC_NO_TEST			=	src/main.c														\
						src/mysh.c

SRC_TEST			=	src/builtin/alias.c												\
						src/builtin/builtin_functions.c									\
						src/builtin/cd.c												\
						src/builtin/env.c												\
						src/builtin/exit.c												\
						src/builtin/fg.c												\
						src/builtin/setenv.c											\
						src/builtin/unalias.c											\
						src/builtin/unsetenv.c											\
						src/env_handlers/create_variable.c								\
						src/env_handlers/find_var_env.c									\
						src/env_handlers/get_var_value.c								\
						src/error_handlers/error.c										\
						src/exec_handlers/eval_exec_cmd.c								\
						src/exec_handlers/exec_piped_commands.c							\
						src/exec_handlers/exec_shell_commands.c							\
						src/file_handlers/find_binary_in_path.c							\
						src/file_handlers/get_path_to_executable.c						\
						src/job_control/check_process.c									\
						src/job_control/process.c										\
						src/parse_input/commands/change_fd.c							\
						src/parse_input/commands/command_struct.c						\
						src/parse_input/commands/parse_cmd_list.c						\
						src/parse_input/file_handling/split_info_from_str.c				\
						src/parse_input/get_arguments/check_and_apply_redir.c			\
						src/parse_input/get_arguments/check_for_parse_elem.c			\
						src/parse_input/get_arguments/get_enums.c						\
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
						src/parse_input/unmatched_handling/check_unmatched_backticks.c	\
						src/parse_input/wildcards_handling/add_args_for_matching.c		\
						src/parse_input/wildcards_handling/alter_parse_by_wildcards.c	\
						src/construct_destroy_shell_t.c									\
						src/print_command_prompt.c										\
						src/sigint_handler.c											\

SRC					=	$(SRC_NO_TEST) $(SRC_TEST)

CFLAGS				=	-Wall -Wextra

CPPFLAGS			=	-I./include -I./include/lib -I./include/mysh

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

coverage:
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches

debug:	CFLAGS += -g
debug:	$(LDLIBS)
	$(CC) -o $(NAME) $(SRC) $(LDFLAGS) $(LDLIBS) $(CFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) unit_tests *.gc*

fclean:	clean
	$(RM) $(NAME)
	$(RM) debug
	make fclean -C lib/my

re:	fclean all

.PHONY:	all -lmy tests_run coverage debug clean fclean re
