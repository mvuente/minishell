/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolpars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:42:13 by mvuente           #+#    #+#             */
/*   Updated: 2020/11/30 21:42:24 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		any_symb(char *delim)
{
	while (*delim != 0x0)
	{
		if (*delim != 0x20)
			return (1);
		delim++;
	}
	return (0);
}

char	*semicolparser(char **line, char *delim, t_genlist **genlist,
		t_all *all)
{
	t_genlist	*tmplist;
	int			pipecount;

	tmplist = *genlist;
	while (tmplist->next)
		tmplist = tmplist->next;
	tmplist->set->consq = 0x3b;
	if ((pipecount = pipefinder(*genlist)))
		ft_pipe(all, *genlist, pipecount);
	else
		executer(*genlist, all, 0);
	if (any_symb(delim + 1))
	{
		cleargenlist(*genlist);
		*genlist = initial_genlist();
	}
	return (*line += 1);
}
