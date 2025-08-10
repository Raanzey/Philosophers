NAME 		= philo
CFLAGS 		= -Wall -Wextra -Werror
SRCS		= philo.c philo_utils.c func.c control.c func_utils.c

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	cc $(CFLAGS) $(OBJECTS)	-o $(NAME)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 