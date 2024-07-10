CC = gcc

CFLAGS = -g -Wall -Werror -Wextra -I./includes/ -I./libft/

SRC = src

OBJ = obj

SRCS = $(SRC)/main.c \
	$(SRC)/builtins/env.c \
	$(SRC)/builtins/pwd.c \
	$(SRC)/builtins/exit.c \
	$(SRC)/builtins/cd.c \
	$(SRC)/builtins/unset.c \
	$(SRC)/builtins/export.c \
	$(SRC)/parse/token.c \
	$(SRC)/parse/tokenizer.c \
	$(SRC)/debug/debug.c \
	$(SRC)/parse/quotes.c \

OBJS = $(SRCS:.c=.o)

#$(OBJ)/%.o: $(SRC)/%.c
#	@$(CC) $(CFLAGS) -o $@ -c $?

NAME = minishell

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(LIBFT):
	@make -C libft && make -C libft clean

clean:
	@rm -rf $(SRC)/*.o
	@make -C libft fclean

fclean: clean
	@rm -f ${NAME}

re: fclean all

run: $(NAME)
	@./minishell

.PHONY: all re fclean clean
