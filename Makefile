##
## EPITECH PROJECT, 2020
## Makefile 42sh
## File description:
## Makefile used to compile the 42sh program.
##

SRC_NO_TEST			=	src/main.c

SRC_TEST			=	src/mysh.c											\
						src/parse_input/parse_input.c						\
						src/parse_input/get_enums.c							\
						src/parse_input/free_parsed_input.c					\
						src/parse_input/add_nodes_to_list.c					\
						src/parse_input/get_arguments/get_quoted_arg.c		\
						src/parse_input/get_arguments/get_unquoted_arg.c	\
						src/parse_input/get_arguments/get_splitter.c		\
						src/parse_input/get_arguments/get_redirection.c		\

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
	$(CC) -o $@ $(SRC) $(LDFLAGS) $(LDLIBS) $(CFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) unit_tests *.gc*

fclean:	clean
	rm -f $(NAME)
	rm -f debug

re:	fclean all

.PHONY:	all -lmy tests_run debug clean fclean re
