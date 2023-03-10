# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frdescam <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/08 17:53:33 by frdescam          #+#    #+#              #
#    Updated: 2021/01/14 18:51:20 by frdescam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES:
.SUFFIXES: .c .o

SHELL		= /bin/sh

NAME		= minishell

SRCS		= \
	./srcs/utils/environ/utils.c			\
	./srcs/utils/environ/utils2.c			\
	./srcs/utils/environ/setters.c			\
	./srcs/utils/environ/environ.c			\
	./srcs/utils/environ/getters.c			\
	./srcs/utils/paths/utils.c				\
	./srcs/utils/paths/chdir.c				\
	./srcs/utils/paths/canonize.c			\
	./srcs/utils/paths/relativize.c			\
	./srcs/utils/paths/exists.c				\
	./srcs/utils/paths/join.c				\
	./srcs/utils/whereis.c					\
	./srcs/utils/main_utils.c				\
	./srcs/utils/main_utils_2.c				\
	./srcs/builtins/builtins.c				\
	./srcs/builtins/export.c				\
	./srcs/builtins/unset.c					\
	./srcs/builtins/env.c					\
	./srcs/builtins/pwd.c					\
	./srcs/builtins/cd.c					\
	./srcs/builtins/echo.c					\
	./srcs/builtins/exit.c					\
	./srcs/main.c							\
	./srcs/handle_errors.c					\
	./srcs/parsing/parse_line.c				\
	./srcs/parsing/parse_cmds.c				\
	./srcs/parsing/parse_redirs_utils.c		\
	./srcs/parsing/parse_redirs.c			\
	./srcs/parsing/post_process_utils.c		\
	./srcs/parsing/post_process_fragments.c	\
	./srcs/parsing/post_process.c			\
	./srcs/exec_line.c						\
	./srcs/exec_pipe_cmd.c

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
