/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:46:54 by mvuente           #+#    #+#             */
/*   Updated: 2020/11/30 21:46:56 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell(t_all all)
{
	size_t	ret;
	char	*line;
	char	buf[1];

	while ((ret = gnl(0, &line)) >= 0)
	{
		if (ret == 0)
		{
			if (!line[0])
			{
				ft_putendl_fd("exit", 1);
				exit(0);
			}
			while ((ret = read(0, buf, 1)) == 0)
			{
			}
		}
		reader(&line, &all);
		if (all.ptr_to_free)
			free(all.ptr_to_free);
	}
	if (ret == 0)
		exit(0);
	read_error();
	return (0);
}
