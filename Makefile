##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

SRC			=	src/main.c

OBJ			=	$(SRC:.c=.o)

NAME		=	myftp

LDLIB		=	-L./lib/

LMY			=	-lmy -lmy_printf

CPPFLAGS	=	-I./includes/ -I./lib/my/include/

LCRITER		= -lcriterion

$(NAME): $(OBJ)
	make -C lib/my/
	make -C lib/my_printf/
	gcc -o $@ $^ $(CPPFLAGS) ${LDLIB} ${LMY}

all: $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C lib/my/
	make clean -C lib/my_printf/

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests*
	make fclean -C lib/my/
	make fclean -C lib/my_printf/

re: fclean $(NAME)

unit_tests:	$(SRC)
	make -C lib/my/
	gcc -o unit_tests $^ tests/test.c $(LDLIB) $(LMY) $(CPPFLAGS) \
	--coverage -lcriterion
	./unit_tests
	gcovr --exclude tests/

.PHONY: all clean fclean re unit_tests
