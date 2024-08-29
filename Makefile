NAME = minishell

CC = gcc

OBJ = obj

SRC = src

CFLAGS = -g -Wall -Wextra -Werror

READLINE_DIR = ./lib/readline-8.2

READLINE_V = $(READLINE_DIR)/lib/libreadline.a

LIBFT_DIR = ./lib/libft

LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(READLINE_DIR)/include -I$(LIBFT_DIR) -I./includes/

DYLIBS = -L$(READLINE_DIR)/lib -lreadline

ifeq ($(shell uname), Linux)
	DYLIBS += -ltinfo
endif

SRCS = $(SRC)/exec/main.c \
	$(SRC)/exec/main_utils.c \
	$(SRC)/exec/exec.c \
	$(SRC)/exec/signals.c \
	$(SRC)/exec/exec_utils.c \
	$(SRC)/builtins/env.c \
	$(SRC)/builtins/pwd.c \
	$(SRC)/builtins/exit.c \
	$(SRC)/builtins/cd.c \
	$(SRC)/builtins/cd_utils.c \
	$(SRC)/builtins/unset.c \
	$(SRC)/builtins/unset_utils.c \
	$(SRC)/builtins/export.c \
	$(SRC)/builtins/export_utils.c \
	$(SRC)/builtins/echo.c \
	$(SRC)/parse/token.c \
	$(SRC)/parse/token2.c \
	$(SRC)/parse/tokenizer.c \
	$(SRC)/parse/quotes.c \
	$(SRC)/parse/syntax.c \
	$(SRC)/parse/expansion.c \
	$(SRC)/parse/expansion_utils.c \
	$(SRC)/parse/argv.c \
	$(SRC)/parse/commands.c \
	$(SRC)/io_operations/pipe.c \
	$(SRC)/io_operations/io_utils.c \
	$(SRC)/io_operations/redirections.c \
	$(SRC)/io_operations/heredoc.c \

OBJS = $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)

all: $(NAME)

$(OBJ):
	@mkdir obj
	@mkdir obj/parse
	@mkdir obj/exec
	@mkdir obj/io_operations
	@mkdir obj/builtins

$(READLINE_DIR):
	@echo "Downloading Readline-8.2..."
	@curl https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz -o readline-8.2.tar.gz 2>&1 | awk '{printf "."; fflush()}'
	@echo ""
	@mkdir ./lib/readline-8.2
	@tar xvfz readline-8.2.tar.gz > /dev/null 2> /dev/null
	@rm readline-8.2.tar.gz

clean:
	@rm -rf $(OBJ)
	@make -C lib/libft fclean

fclean: clean
	@rm -f ${NAME}

re: fclean all

run: $(NAME)
	@./minishell

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -o $@ -c $(INCLUDES) $?

$(LIBFT):
	@make -C lib/libft && make -C lib/libft clean

$(NAME): $(READLINE_V) $(LIBFT) $(OBJS) 
	$(CC) $(CFLAGS) -o $(NAME) $(INCLUDES) $(OBJS) $(DYLIBS) $(LIBFT)

$(READLINE_V): | $(READLINE_DIR)
	@echo "Compiling Readline-8.2..."
	@cd readline-8.2 && ./configure --prefix=$(PWD)/$(READLINE_DIR) 2>&1 | awk '{printf "."; fflush()}'
	@cd readline-8.2 && make install 2>&1 | awk '{printf "."; fflush()}'
	@printf "\n"
	@rm -rf readline-8.2

ifeq ($(shell uname), Linux)
leak: re
	@valgrind --leak-check=full --track-origins=yes ./minishell
else
leak: re
	@bash ./minishell.sh
	@make run
endif

.PHONY: all re fclean clean
