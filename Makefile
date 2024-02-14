##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

SRC			=	src/main.c

OBJ			=	$(SRC:.c=.o)

NAME		=	myftp



CPPFLAGS	=	-I./includes/

LCRITER		= -lcriterion

$(NAME): $(OBJ)
	gcc -o $@ $^ $(CPPFLAGS) ${LDLIB} ${LMY}

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests*

re: fclean $(NAME)

unit_tests:	$(SRC)
	gcc -o unit_tests $^ tests/test.c $(LDLIB) $(LMY) $(CPPFLAGS) \
	--coverage -lcriterion
	./unit_tests
	gcovr --exclude tests/

.PHONY: all clean fclean re unit_tests
