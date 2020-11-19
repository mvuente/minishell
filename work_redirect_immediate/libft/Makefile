# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvuente <mvuente@student.21-school.ru      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/27 10:03:43 by mvuente           #+#    #+#              #
#    Updated: 2020/05/27 12:53:17 by mvuente          ###   ########.fr        #
#                                                                              #
# **************************************************************************** 

NAME = libft.a

SRC = ft_strchr.c ft_strjoin.c ft_tolower.c ft_bzero.c ft_memmove.c \
	ft_strlen.c ft_memcmp.c ft_calloc.c ft_memcpy.c ft_isalnum.c \
	ft_strdup.c ft_strlcpy. ft_strlcat.c ft_strncmp.c ft_putsr_fd.c \
	ft_putchar_fd.c 

OBJ = $(SRC:.c=.o)

H = libft.h

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $?
	ranlib $(NAME)

%.o: %.c $(H)
	gcc -Wall -Wextra -Werror -c $< -o $@ -I.

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all