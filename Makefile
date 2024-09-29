
CC = cc

CF = -Wall -Wextra -Werror -g -fsanitize=thread

NAME = philo

SRC = philo.c utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CF) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CF) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re