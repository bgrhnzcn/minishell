CC = gcc

CFLAGS = -g -Wall -Wextra -fsanitize=address -fsanitize=leak -I./includes/ -I./libft/

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
	$(SRC)/parse/expansion.c \

OBJS = $(SRCS:.c=.o)

#$(OBJ)/%.o: $(SRC)/%.c
#	@$(CC) $(CFLAGS) -o $@ -c $?

NAME = minishell

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(LIBFT):
	make -C libft && make -C libft clean

clean:
	cd $(SRC) && rm -rf builtins/*.o debug/*.o \
				parse/*.o pipe/*.o string/*.o *.o
	make -C libft fclean

fclean: clean
	rm -f ${NAME}

re: fclean all

run: $(NAME)
	./minishell

.PHONY: all re fclean clean
