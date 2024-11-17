SRCS        = main.c utils.c routine.c init.c routine_utils.c after_t_forks.c eat_t_sup_die_t.c sleep_t_sup_die_t.c
OBJ_DIR     = obj
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
NAME        = philo
CC          = cc
RM          = rm -f
CFLAGS      = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
