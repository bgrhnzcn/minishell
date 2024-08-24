NAME = minishell

CC = gcc

OBJ = obj

SRC = src

CFLAGS = -g -Wall -Wextra -Werror -I./includes/ -I./lib/libft/ -I./lib/readline-8.2/include/

INCLUDE = -I./lib/readline-8.2/include

READLINE_V = lib/readline-8.2/lib/libreadline.a

LIBFT = lib/libft/libft.a

DYLIBS = -L./lib/readline-8.2/lib -lreadline

ifeq ($(shell uname), Linux)
	DYLIBS += -ltinfo
endif

SRCS = $(SRC)/exec/main.c \
	$(SRC)/exec/exec.c \
	$(SRC)/exec/signals.c \
	$(SRC)/exec/exec_utils.c \
	$(SRC)/builtins/env.c \
	$(SRC)/builtins/pwd.c \
	$(SRC)/builtins/exit.c \
	$(SRC)/builtins/cd.c \
	$(SRC)/builtins/unset.c \
	$(SRC)/builtins/unset_utils.c \
	$(SRC)/builtins/unset_utils2.c \
	$(SRC)/builtins/export.c \
	$(SRC)/builtins/export_utils.c \
	$(SRC)/builtins/echo.c \
	$(SRC)/parse/token.c \
	$(SRC)/parse/token2.c \
	$(SRC)/parse/tokenizer.c \
	$(SRC)/parse/quotes.c \
	$(SRC)/parse/syntax.c \
	$(SRC)/parse/expansion.c \
	$(SRC)/parse/argv.c \
	$(SRC)/parse/commands.c \
	$(SRC)/parse/parse_utils.c \
	$(SRC)/io_operations/pipe.c \
	$(SRC)/io_operations/io_utils.c \
	$(SRC)/io_operations/redirections.c \
	$(SRC)/io_operations/heredoc.c \

OBJS = $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)

all: $(NAME)

$(OBJ):
	mkdir obj
	mkdir obj/parse
	mkdir obj/exec
	mkdir obj/io_operations
	mkdir obj/builtins

clean:
	rm -rf $(OBJ)
	make -C lib/libft fclean

fclean: clean
	rm -f ${NAME}

re: fclean all

run: $(NAME)
	./minishell

ifeq ($(shell uname), Linux)
leak: re
	@valgrind --leak-check=full --track-origins=yes ./minishell
else
leak: re
	@bash ./minishell.sh
	@make run
endif

ifeq ($(shell uname), Linux)
debug: re
	@gdb ./minishell
else
debug: re
	@lldb ./minishell
endif

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -o $@ -c $(INCLUDE) $?

$(LIBFT):
	make -C lib/libft && make -C lib/libft clean

$(NAME): $(READLINE_V) $(LIBFT) $(OBJ) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(INCLUDE) $(OBJS) $(DYLIBS) $(LIBFT)

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

.PHONY: all re fclean clean
