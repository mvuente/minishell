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

char	*semicolparser(char **line, t_genlist **genlist, t_all *all)
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
	*genlist = initial_genlist();
	return (*line += 1);
}
