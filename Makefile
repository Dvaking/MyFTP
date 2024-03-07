##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

SRC			=	main.c			\
				my_ftp.c		\
				$(DIR_TOOLBOX)	\
				$(DIR_SERVER)	\

TOOLBOX		=	check_args.c			\
				socket_initialization.c	\

SERVER		=	connection.c			\
				get_information.c		\

TEST		=	test.c

DIR_SRC		=	$(addprefix src/, $(SRC))
DIR_TESTS	=	$(addprefix tests/, $(TEST))
DIR_TOOLBOX	=	$(addprefix toolbox/, $(TOOLBOX))
DIR_SERVER	=	$(addprefix server/, $(SERVER))

OBJ_SRC		=	$(DIR_SRC:.c=.o)
OBJ			=	$(OBJ_SRC)

NAME		=	myftp

CPPFLAGS	=	-I./includes/ -I./lib/my/include/

WFLAGS		=	-W -Wall -Wextra

LCRITER		= --coverage -lcriterion

$(NAME): $(OBJ)
	gcc -o $@ $^ $(WFLAGS)

debug: fclean
	gcc -o $(NAME) $(DIR_SRC) $(CPPFLAGS) $(WFLAGS) -ggdb3

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf unit_tests/

re: fclean $(NAME)

unit_tests: fclean
	mkdir unit_tests
	gcc -o unit_tests/unit_tests $(DIR_SRC) $(DIR_TESTS) \
	$(CPPFLAGS) $(WFLAGS) $(LCRITER)

tests_run:	unit_tests
	./unit_tests

.PHONY: all clean fclean re unit_tests tests_run
