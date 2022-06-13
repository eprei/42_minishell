# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 14:54:43 by olmartin          #+#    #+#              #
#    Updated: 2022/06/06 11:14:53 by Emiliano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
			ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
			ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
			ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
			ft_toupper.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
			ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c \
			ft_lstsize.c ft_printf.c ft_printf_idu.c ft_printf_s.c ft_printf_x.c \
			utils/ft_itoa_printf.c utils/utils.c ft_rev_tab.c ft_substr_gnl.c \
			get_next_line.c get_next_line_utils.c

OBJS		= ${SRCS:.c=.o}

OBJS_BONUS 	= ${SRCS_BONUS:.c=.o}

NAME		= libft.a

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Werror -Wextra

.c.o:	
			@ ${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}	
			@ ar rc ${NAME} ${OBJS}
			@ ranlib ${NAME}

all:		${NAME}

bonus : 	${OBJS_BONUS}
			ar rc ${NAME} ${OBJS_BONUS}
			ranlib ${NAME}

lib:		${OBJS}
			ar rc ${NAME}
			ranlib ${NAME}

.PHONY:		all clean fclean  re

clean:	
			@ ${RM} ${OBJS}
			@ ${RM} ${OBJS_BONUS}

fclean:		clean
			@ ${RM} ${NAME}

re:			fclean all
