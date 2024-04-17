SRCS = get_next_line.c get_next_line_utils.c

BONUS_SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c

NAME = get_next_line.a

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

FLAGS = -g -Wall -Wextra -Werror

CC = gcc

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)
	rm -rf a.out

re:	fclean all

bonus: $(OBJS) $(BONUS_OBJS)
	ar -rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY: all clean fclean re