# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frdescam <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/21 16:00:31 by frdescam          #+#    #+#              #
#    Updated: 2021/01/14 18:05:19 by badam            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = \
ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_itoa.c \
ft_memcpy.c ft_memmove.c ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c \
ft_string_destroy.c ft_string_new.c ft_string_push.c ft_string_remove.c \
ft_string_sub.c ft_string_with_capacity.c ft_strjoin.c ft_strlcpy.c \
ft_strlen.c ft_strncmp.c ft_strnstr.c ft_substr.c \
 \
lst/ft_lstadd_back.c lst/ft_lstlast.c lst/ft_lstnew.c

OBJS = ${SRCS:.c=.o}

CC		= cc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror -g3

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY : all clean fclean re
