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

NAME = minishell
LIBFT = libft.a

SRC =   direct.c errors.c gnl.c biglist_operations.c minishell.c \
		parser.c process.c record.c token.c utils.c execute.c pwd.c \
		exec_redirect.c dollar.c hballaba.c environ.c utils2.c \
		list_operations.c export.c cd.c unset.c env.c exit.c

SRC_LIB_DIR = libft/

OBJ = $(SRC:.c=.o)

SHELL_H = minishell.h
LIB_H = libft.h

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(SRC_LIB_DIR)
	cp $(SRC_LIB_DIR)$(LIBFT) .
	mv $(LIBFT) $(NAME)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME) 

%.o: %.c  $(SHELL_H) $(LIB_H)
	gcc -Wall -Wextra -Werror -c $< -o $@ -I .

clean:
	rm -f $(OBJ)
	@make -C $(SRC_LIB_DIR) clean

fclean: clean
	rm -f $(NAME) bash
	@make -C $(SRC_LIB_DIR) fclean

re: fclean all

bash: all
	gcc test.c minishell -o bash