##
## EPITECH PROJECT, 2019
## Makefile 42sh
## File description:
## Compiles c files with libs into the 42sh program
##

MAIN		=	src/main.c												\

SRC			=															\

SRCTESTS	=	tests/													\

VPATH		=	/usr/local/lib/

NAME		=	42sh

CFLAGS		=	-Wall -Wextra

CPPFLAGS	=	-I./include/

LDFLAGS		=	-L./lib/

LDLIBS		+=	-lmy

all:	$(NAME)

$(NAME):
	$(MAKE) -sC lib/my
	$(CC) -o $@ $(MAIN) $(SRC) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

debug:
	$(MAKE) -sC lib/my
	$(CC) -g -o $@ $(SRC) $(MAIN) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

tests_run:
	$(MAKE) -sC lib/my
	$(CC) -o $@ $(SRC) $(SRCTESTS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -lcriterion --coverage
	./$@
	$(RM) $@

coverage:
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches

clean:
	$(RM) tests_run
	$(RM) *.gcda *.gcno
	$(RM) vgcore.*

fclean:	clean
	$(RM) $(NAME)
	$(RM) debug
	$(MAKE) fclean -sC lib/my

re:	fclean all

.NOTPARALLEL:
.PHONY: all debug tests_run coverage clean fclean re