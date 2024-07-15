CC = gcc

CFLAGS = -g -Wall -Wextra -I./includes/ -I./libft/

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
	$(SRC)/parse/token2.c \
	$(SRC)/parse/tokenizer.c \
	$(SRC)/debug/debug.c \
	$(SRC)/parse/quotes.c \
	$(SRC)/parse/syntax.c \
	$(SRC)/parse/expansion.c \
	$(SRC)/parse/argv.c \
	$(SRC)/parse/commands.c \
	$(SRC)/io_operations/pipe.c \
	$(SRC)/io_operations/redirections.c \
	$(SRC)/exec/exec.c \

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
			parse/*.o io_operations/*.o string/*.o exec/*.o *.o
	make -C libft fclean

fclean: clean
	rm -f ${NAME}

re: fclean all

run: $(NAME)
	./minishell

leak: re
	@bash ./minishell.sh
	@make run

.PHONY: all re fclean clean
