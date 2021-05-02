/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:21:04 by mvuente           #+#    #+#             */
/*   Updated: 2020/11/30 22:21:07 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_error(void)
{
	write(2, "An error while reading the line\n", 32);
	exit(1);
}

void	malloc_error(void)
{
	write(2, "An error while memory allocating\n", 33);
	exit(1);
}

int		delim_error(char *delim, int flag)
{
	errno = 258;
	write(2, "bash_na_bash: ", 14);
	write(2, "syntax error near unexpected token", 34);
	write(2, "`", 1);
	write(2, delim, 1);
	if (flag == 2)
		write(2, delim, 1);
	write(2, "\'", 1);
	write(2, "\n", 1);
	return (1);
}

int		empt_dir_error(void)
{
	errno = 258;
	ft_putendl_fd(\
	"bash_na_bash: syntax error near unexpected token `newline'", 2);
	return (1);
}

char	*open_cq_error(void)
{
	errno = 258;
	ft_putendl_fd(\
	"bash_na_bash: syntax error: opened quotation", 2);
	return (NULL);
}
