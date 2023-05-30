NAME = philo

SRC = main.c philo.c time.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

CC = cc

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
