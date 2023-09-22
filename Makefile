NAME = pipex
FLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a
LIB_DIR = libft
SRCS = main.c check.c parse.c processes.c error.c utils.c split2.c
OBJS = $(addprefix obj/, $(SRCS:.c=.o))
CC = gcc

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@printf "pipex compiled\n"

obj/%.o: %.c
	@$(CC) -g $(FLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIB_DIR)

clean:
	rm -f $(OBJS)
	make -C ./libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re