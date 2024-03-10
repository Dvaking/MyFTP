##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

SRC			=	main.c			\
				my_ftp.c		\
				$(DIR_SERVER)	\
				$(DIR_TOOLBOX)	\

TOOLBOX		=	check_args.c		\
				initialization.c	\
				remove_line_break.c	\

SERVER		=	client.c			\
				server.c			\
				$(DIR_COMMANDS)		\

COMMANDS	=	command.c			\
				$(DIR_FOLDER)		\
				$(DIR_CONNECTION)	\

CONNECTION	=	authentification.c	\
				disconnection.c		\

FOLDER		=	move_in_folder.c	\
				pwd.c				\

TEST		=	test.c

DIR_SRC			=	$(addprefix src/, $(SRC))
DIR_TESTS		=	$(addprefix tests/, $(TEST))
DIR_TOOLBOX		=	$(addprefix toolbox/, $(TOOLBOX))
DIR_SERVER		=	$(addprefix server/, $(SERVER))

DIR_COMMANDS	=	$(addprefix commands/, $(COMMANDS))
DIR_CONNECTION	=	$(addprefix connection/, $(CONNECTION))
DIR_FOLDER		=	$(addprefix folder_interraction/, $(FOLDER))

OBJ_SRC		=	$(DIR_SRC:.c=.o)
OBJ			=	$(OBJ_SRC)

NAME		=	myftp

CPPFLAGS	=	-I./includes/ -I./lib/my/include/

WFLAGS		=	-W -Wall -Wextra

LMY			=	-L./lib/ -lmy

LCRITER		= --coverage -lcriterion

$(NAME): $(OBJ)
	make -C lib/my
	gcc -o $@ $^ $(WFLAGS) $(LMY)

debug: fclean
	make -C lib/my
	gcc -o $(NAME) $(DIR_SRC) $(CPPFLAGS) $(WFLAGS) $(LMY) -ggdb3

all: $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C lib/my

fclean: clean
	rm -f $(NAME)
	rm -rf unit_tests/
	make fclean -C lib/my

re: fclean $(NAME)

unit_tests: fclean
	make -C lib/my
	mkdir unit_tests
	gcc -o unit_tests/unit_tests $(DIR_SRC) $(DIR_TESTS) \
	$(CPPFLAGS) $(WFLAGS) $(LCRITER) $(LMY)

tests_run:	unit_tests
	./unit_tests

.PHONY: all clean fclean re unit_tests tests_run
