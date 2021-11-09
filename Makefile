C = gcc
FLAG = -Wall -Wextra -Werror
NAME = philo
SRC = main.c philo.c utils.c supervisor.c

all: $(NAME)

$(NAME):	$(SRC)
			$(C) $(FLAG) $(SRC) -o $(NAME)

debug:	$(SRC)
			$(C) $(FLAG) $(SRC) -o $(NAME) -g -fsanitize=address

clean:
		rm -rf *.o
fclean:	clean
		rm -rf $(NAME)

re: fclean all