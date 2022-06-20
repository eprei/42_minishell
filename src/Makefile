# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/03 15:01:40 by Emiliano          #+#    #+#              #
#    Updated: 2022/06/20 16:13:42 by olmartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

NAMELIBFT = libft.a

SRCS = exec_test.c signals.c split.c subsplit.c exit.c init_data.c var_builtin.c \
	utils_tab.c lexer.c utils_lexer.c expander.c var_utils.c pipes_pids.c \
	exec.c open_files.c mini_builtins.c

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g

CC = gcc

LIBFTPATH = ../libft

all: $(NAME)

$(NAME): $(OBJ)
	@ make -C $(LIBFTPATH)
# mac 42
	@ CC $(CFLAGS) $(SRCS) -L$(LIBFTPATH) -lft -L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib -lreadline -I /Users/$(USER)/.brew/Cellar/readline/8.1.2/include -o $(NAME)
# home mac
#	@ CC $(SRCS) -L$(LIBFTPATH) -lft -L/usr/include -lreadline -o $(NAME)


clean:
	@rm -rf $(OBJ)
	@make clean -C $(LIBFTPATH)

fclean: clean
	@ rm -rf $(NAME)
	@ make fclean -C $(LIBFTPATH)

re: fclean all

.PHONY: all clean fclean re
