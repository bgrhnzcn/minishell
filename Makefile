CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRCS = srcs/main.c

OBJS = $(SRCS:.c=.o)

NAME = minishell

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) -I . $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(LIBFT):
	cd libft && make

clean:
	cd srcs && rm -rf *.o
	cd libft && make fclean

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all re fclean clean
