/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cqprocessor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:21:22 by mvuente           #+#    #+#             */
/*   Updated: 2020/11/30 22:21:25 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*closest_cq(char *line, char cq)
{
	char	*ptr;

	ptr = line;
	while (*ptr != 0x0)
	{
		if (*ptr == cq)
			return (ptr);
		ptr++;
	}
	return (NULL);
}

int		is_open_cqs(char *line, char *delimiter, char *quotset)
{
	char	*ptr;
	char	*closest;

	if (*delimiter != 0x7c && *delimiter != 0x3b)
		return (2);
	ptr = line;
	while (*ptr != 0x0)
	{
		if (ft_strchr(quotset, *ptr) && ptr < delimiter &&
		(closest = closest_cq(ptr + 1, *ptr)) && closest > delimiter)
			return (1);
		ptr++;
	}
	return (0);
}

char	*cqpars(char **line, char *tmp, char symb, t_all *all)
{
	char	*finish;
	int		finflag;

	finflag = 0;
	finish = tmp + 1;
	while (*finish != symb && *finish != 0x0 && !finflag)
	{
		if (*finish == 0x24 && symb == 0x22)
		{
			finish = dollarpars(line, finish, all);
			finflag = 1;
		}
		finish++;
	}
	if (*finish == 0x0)
		return (open_cq_error());
	if (finflag)
		finish--;
	return (finish + 1);
}

char	*cqprocessor(char *item, char **cqptr, int dolflag, t_all all)
{
	char	*quot;
	char	*start;
	char	*finish;
	char	*tmp;

	if (dolflag)
	{
		start = *cqptr;
		quot = *cqptr;
		finish = cqpars(&tmp, quot, *quot, &all) - 1;
		finish = ft_memmove(finish, finish + 1, ft_strlen(finish + 1) + 1);
		start = (ft_memmove(start, start + 1, ft_strlen(start + 1) + 1));
		*cqptr = finish - 1;
	}
	return (item);
}
