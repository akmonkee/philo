NAME = philo

SRC = main.c philo_gen.c utils.c thread_gen.c philo_actions.c monitor.c

OUT = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra

%.c%.o:
		${CC} ${FLAGS} -g -c $< -o ${<:.c=.o}

$(NAME) : $(OUT)
		$(CC) $(FLAGS) $(OUT) -o $(NAME)

all: $(NAME)

clean:
		rm -f $(OUT)

fclean: clean
	rm -f $(NAME)

re: fclean all
