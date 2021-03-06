/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:21:56 by mvuente           #+#    #+#             */
/*   Updated: 2020/11/30 22:21:59 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dirlist	*dir_record(t_set *set, char *direct, char *operand)
{
	t_dirlist	*tmp;

	tmp = set->direct;
	if (!tmp)
		return (dirlistcrtr(direct, operand));
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = dirlistcrtr(direct, operand);
	return (set->direct);
}

char		*dirpars(char **line, char *start, t_set *set, t_all *all)
{
	char		*tmp;
	char		*direct;

	while (*start == 0x3c || *start == 0x3e)
		start++;
	direct = itemcrtr(line, start, 0, *all);
	tmp = start;
	while (*tmp != 0x0)
	{
		if (*tmp == 0x20)
			tmp++;
		else
			break ;
	}
	*line = tmp;
	while (*tmp != 0x0 && !ft_strchr(all->delimiters, *tmp))
	{
		if (ft_strchr(all->quot, *tmp))
			tmp = cqpars(line, tmp, *tmp, all);
		else
			tmp++;
	}
	set->direct = dir_record(set, direct, itemcrtr(line, tmp, 1, *all));
	return (tmp);
}
