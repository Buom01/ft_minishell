# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frdescam <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/08 17:53:33 by frdescam          #+#    #+#              #
#    Updated: 2020/09/30 00:10:11 by frdescam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES:
.SUFFIXES: .c .o

SHELL		= /bin/sh

NAME		= minishell

SRCS		= \
	./srcs/utils/environ/utils.c	\
	./srcs/utils/environ/setters.c	\
	./srcs/utils/environ/environ.c	\
	./srcs/utils/environ/getters.c	\
	./srcs/utils/whereis.c			\
	./srcs/builtins/builtins.c		\
	./srcs/builtins/export.c		\
	./srcs/builtins/unset.c			\
	./srcs/builtins/env.c			\
	./srcs/main.c					\
	./srcs/handle_errors.c			\
	./srcs/parsing/exec_line.c		\
	./srcs/parsing/exec_cmd.c

OBJS		= ${SRCS:.c=.o}

CC			= cc
RM			= rm -f

LIBFT_FLAGS	= -Llibft -lft

CFLAGS		= -Wall -Wextra -Werror -g3 -Isrcs

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
