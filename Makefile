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
LIBSHELL = libshell.a

SRC =   direct.c errors.c gnl.c biglist_operations.c minishell.c \
		parser.c process.c record.c token.c utils.c execute.c pwd.c \
		exec_redirect.c dollar.c hballaba.c environ.c utils2.c \
		list_operations.c export.c cd.c unset.c env.c exit.c syscall.c \
		pipepars.c semicolpars.c pipe_exec.c lists.c cqprocessor.c \
		sys_utils.c validator.c cd_utils.c test.c

SRC_LIB_DIR = libft/

OBJ = $(SRC:.c=.o)

MIN_H = minishell.h

CC = gcc

FLAGS = -Wall -Wextra -Werror 

SHELL_H = minishell.h
LIB_H = libft.h

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(SRC_LIB_DIR)
	cp $(SRC_LIB_DIR)$(LIBFT) .
	$(CC) $(FLAGS) $(OBJ) -L. $(LIBFT) -o $(NAME)

%.o: %.c  $(MIN_H)
	$(CC) $(FLAGS) -c $< -o $@ -I $(MIN_H)
 
clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	@make -C $(SRC_LIB_DIR) fclean

re: fclean all
