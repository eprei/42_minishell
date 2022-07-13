NAME = minishell

NAMELIBFT = libft.a

SRCS = main.c signals.c split.c subsplit.c init_data.c var_builtin.c \
	utils_tab.c lexer.c lexer_utils.c expander.c var_utils.c pipes_pids.c \
	exec.c open_files.c mini_builtins.c parsing.c prepare_exec.c \
	prep_builtin_exec.c error.c check_builtin_and_redir.c expander_utils.c \
	node_t_cmd_create.c node_t_cmd_fill.c print_list.c termios.c free.c \
	quotes.c


OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

DEBUG_FLAG = -g

LDFLAGS= /usr/local/Cellar/readline/8.1.2/lib

CPPFLAGS= /usr/local/opt/readline/include

CC = gcc

LIBFTPATH = ../libft

all: $(NAME)

.c.o:
# mac 42
	$(CC) -I /Users/$(USER)/.brew/Cellar/readline/8.1.2/include $(CFLAGS) $(DEBUG_FLAG) -c $^ -o $@
# home mac
#	$(CC) -I $(CPPFLAGS) $(CFLAGS) $(DEBUG_FLAG) -c $^ -o $@

$(NAME): $(OBJ)
	 make -C $(LIBFTPATH)
# mac 42
	 $(CC) $(CFLAGS) -g $(OBJ) -L$(LIBFTPATH) -lft -L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib -lreadline -o $(NAME)
# home mac
#	@ $(CC) $(OBJ) -L$(LIBFTPATH) -lft -L $(LDFLAGS) -lreadline -o $(NAME)

clean:
	@rm -rf $(OBJ)
	@make clean -C $(LIBFTPATH)

fclean: clean
	@ rm -rf $(NAME)
	@ make fclean -C $(LIBFTPATH)

re: fclean all

.PHONY: all clean fclean re
