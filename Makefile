CC = cc
FLAGS = -Wall -Wextra -Werror 

NAME = philo
SRC = philo.c utils.c parse.c monitor.c routine.c
OBJ = $(SRC:.c=.o)
HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all