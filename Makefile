CC = gcc

CFLAGS = -g -Wall -Wextra -L./lib/readline-8.2/lib -I./includes/ -I./lib/libft/ -I./lib/readline-8.2/include/

SRC = src

OBJ = obj

SRCS = $(SRC)/main.c \
	$(SRC)/builtins/env.c \
	$(SRC)/builtins/pwd.c \
	$(SRC)/builtins/exit.c \
	$(SRC)/builtins/cd.c \
	$(SRC)/builtins/unset.c \
	$(SRC)/builtins/export.c \
	$(SRC)/builtins/echo.c \
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

READLINE_V = lib/readline-8.2/lib/libreadline.a

LIBFT = lib/libft/libft.a

all: $(NAME)

$(NAME): $(READLINE_V) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(LIBFT):
	make -C lib/libft && make -C lib/libft clean

clean:
	cd $(SRC) && rm -rf builtins/*.o debug/*.o \
			parse/*.o io_operations/*.o string/*.o exec/*.o *.o
	make -C lib/libft fclean

fclean: clean
	rm -f ${NAME}

re: fclean all

run: $(NAME)
	./minishell

$(READLINE_V):
	@if [ ! -d "./lib/readline-8.2" ]; then\
		echo "Downloading Readline-8.2...";\
		curl https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz -o readline-8.2.tar.gz;\
		mkdir ./lib/readline-8.2;\
		tar xvfz readline-8.2.tar.gz > /dev/null 2> /dev/null;\
		rm readline-8.2.tar.gz;\
	fi;\
	if [ ! -f "./$(READLINE_V)" ]; then\
		echo "Compiling Readline-8.2...";\
		cd readline-8.2 && ./configure --prefix=$(PWD)/lib/readline-8.2 2>&1 | awk '{printf "."; fflush()}';\
		cd .. && make -C readline-8.2 install 2>&1 | awk '{printf "."; fflush()}';\
		rm -rf readline-8.2;\
	fi;

leak: re
	@bash ./minishell.sh
	@make run

.PHONY: all re fclean clean
