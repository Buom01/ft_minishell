# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frdescam <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/08 17:53:33 by frdescam          #+#    #+#              #
#    Updated: 2020/09/15 13:49:08 by frdescam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES:
.SUFFIXES: .c .o

SHELL		= /bin/sh

NAME		= minishell

SRCS		=

OBJS		= ${SRCS:.c=.o}

CC			= cc
RM			= rm -f

LIBFT_FLAGS	= -Llibft -lft

CFLAGS		= -Wall -Wextra -Werror -g3

INCLUDES	= -I libft

all:	${NAME}

.c.o:
		${CC} ${INCLUDES} ${CFLAGS} -c $< -o $@

$(NAME): ${OBJS}
		make -C libft
		${CC} ${OBJS} ${LIBFT_FLAGS} -o ${NAME} 
clean:
		make -C libft clean
		${RM} ${OBJS}


fclean:	clean
		rm -f libft/libft.a
		${RM} ${NAME}

re:		fclean
	make all

.PHONY : all clean fclean re
