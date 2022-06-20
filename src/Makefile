# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/03 15:01:40 by Emiliano          #+#    #+#              #
#    Updated: 2022/06/20 10:23:27 by Emiliano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

NAMELIBFT = libft.a

SRCS = main.c signals.c split.c subsplit.c exit.c init_data.c var_builtin.c \
	utils_tab.c lexer.c lexer_utils.c expander.c var_utils.c pipes_pids.c \
	exec.c mini_here.c mini_builtins.c

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g

LDFLAGS= /usr/local/Cellar/readline/8.1.2/lib

CPPFLAGS= /usr/local/opt/readline/include

CC = gcc

LIBFTPATH = ../libft

all: $(NAME)

$(NAME):
	@ make -C $(LIBFTPATH)
# mac 42
#	@ CC $(CFLAGS) $(SRCS) -L$(LIBFTPATH) -lft -L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib -lreadline -I /Users/$(USER)/.brew/Cellar/readline/8.1.2/include -o $(NAME)
# home mac
	@ CC $(SRCS) -L$(LIBFTPATH) -lft -L $(LDFLAGS) -lreadline -I $(CPPFLAGS) -o $(NAME)


clean:
	@rm -rf $(OBJ)
	@make clean -C $(LIBFTPATH)

fclean: clean
	@ rm -rf $(NAME)
	@ make fclean -C $(LIBFTPATH)

re: fclean all

.PHONY: all clean fclean re
