/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipepars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:45:05 by mvuente           #+#    #+#             */
/*   Updated: 2020/11/30 21:45:09 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pipeparser(char **line, char *delim, t_genlist *templist)
{
	templist->set->consq = *delim;
	templist->next = initial_genlist();
	return (*line += 1);
}

int		pipefinder(t_genlist *genlist)
{
	t_genlist	*temp;
	int			pipecount;

	temp = genlist;
	pipecount = 0;
	while (temp)
	{
		if (temp->set->consq == 0x7c)
			pipecount++;
		temp = temp->next;
	}
	return (pipecount);
}
