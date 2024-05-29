CC = gcc

CFLAGS = -g -Wall -Werror -Wextra -I./includes/ -I./libft/

SRCS = srcs/main.c srcs/builtins/env.c srcs/builtins/pwd.c \
	   srcs/builtins/cd.c srcs/builtins/unset.c srcs/builtins/export.c \
	   srcs/debug/debug.c

OBJS = $(SRCS:.c=.o)

NAME = minishell

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(LIBFT):
	cd libft && make

clean:
	cd srcs && rm -rf *.o
	cd libft && make fclean

fclean: clean
	rm -f ${OBJS}
	rm -f ${NAME}

re: fclean all

.PHONY: all re fclean clean
