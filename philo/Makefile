SRCS        = main.c utils.c routine.c init.c routine_utils.c
OBJS        = $(SRCS:.c=.o)
NAME        = philo
CC          = cc
RM          = rm -f
CFLAGS      = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)

	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re