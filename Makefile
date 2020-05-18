##
## EPITECH PROJECT, 2020
## Makefile 42sh
## File description:
## Makefile used to compile the 42sh program.
##

SRC_MAIN			=	src/main.c											\

SRC_CORE 			=	src/setup_mysh.c									\

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
						src/parse_input/get_arguments/get_quoted_arg.c		\
						src/parse_input/get_arguments/get_unquoted_arg.c	\
						src/parse_input/get_arguments/get_splitter.c		\
						src/parse_input/get_arguments/get_redirection.c		\

SRC_DCLL			=	src/dcll/add_dcll.c									\
						src/dcll/free_dcll.c								\

SRC					=	$(SRC_CORE) $(SRC_ENV) $(SRC_PARSE_INPUT) $(SRC_DCLL)

CFLAGS				=	-Werror -Wextra

CPPFLAGS			=	-I ./include/lib -I ./include/mysh -I ./include

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

coverage:
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches

debug:	CFLAGS += -g
debug:	$(LDLIBS)
	$(CC) -o $@ $(SRC) $(LDFLAGS) $(LDLIBS) $(CFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) unit_tests *.gc*

fclean:	clean
	$(RM) $(NAME)
	$(RM) debug
	$(MAKE) $@ -C ./lib/my

re:	fclean all

.PHONY:	all -lmy tests_run coverage debug clean fclean re
