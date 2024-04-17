CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRCS = srcs/main.c

OBJS = $(SRCS:.c=.o)

NAME = minishell

LIBFT = libs/libft/libft.a

LIBFTPRINTF = libs/ft_printf/libftprintf.a

GET_NEXT_LINE = libs/get_next_line/get_next_line.a

all: $(NAME)

$(NAME): $(LIBFT) $(LIBFTPRINTF) $(GET_NEXT_LINE) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIBFTPRINTF) $(GET_NEXT_LINE)

$(LIBFT):
	cd libs/libft && make

$(LIBFTPRINTF):
	cd libs/ft_printf && make

$(GET_NEXT_LINE):
	cd libs/get_next_line && make bonus

clean:
	cd srcs && rm -rf *.o
	cd libs/libft && make fclean
	cd libs/ft_printf && make fclean
	cd libs/get_next_line && make fclean

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all re fclean clean
