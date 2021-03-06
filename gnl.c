/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:49:26 by mvuente           #+#    #+#             */
/*   Updated: 2020/11/30 21:49:32 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*bufrecorder(char *tmp, char buf)
{
	char	*old;
	size_t	length;

	old = tmp;
	length = ft_strlen(old);
	if (!(tmp = (char*)malloc(sizeof(char) * length + 2)))
		malloc_error();
	ft_bzero(tmp, length + 2);
	ft_memmove(tmp, old, length);
	tmp[length] = buf;
	free(old);
	return (tmp);
}

size_t			gnl(int fd, char **line)
{
	size_t	ret;
	char	buf[1];
	char	*tmp;

	fd = 0;
	if (!(tmp = (char*)malloc(sizeof(char))))
		malloc_error();
	*tmp = '\0';
	*line = tmp;
	write(1, "bash_na_bash! ", 14);
	while ((ret = read(0, buf, 1) > 0))
	{
		if (buf[0] != '\n')
		{
			tmp = bufrecorder(tmp, buf[0]);
			*line = tmp;
		}
		else
			return (ret);
	}
	if (!ret)
		return (0);
	return (-1);
}
