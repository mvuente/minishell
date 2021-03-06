/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:41:03 by mvuente           #+#    #+#             */
/*   Updated: 2020/11/30 21:41:06 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*textpars(char **line, char *tmp, t_set *set, t_all all)
{
	*set = builtinrcrdr(itemcrtr(line, tmp, 0, all), *set);
	return (tmp);
}

char	*tokencrtr(char **line, char *delim, t_genlist **genlist, t_all *all)
{
	t_genlist	*templist;

	templist = *genlist;
	while (templist->next)
		templist = templist->next;
	if (*line < delim)
		return (textpars(line, delim, templist->set, *all));
	else if (*delim == 0x7c)
		return (pipeparser(line, delim, templist));
	else if (*delim == 0x3b)
		return (semicolparser(line, delim, genlist, all));
	else if (*delim == 0x3c || *delim == 0x3e)
		return (dirpars(line, delim, templist->set, all));
	else if (*delim == 0x20)
		return (*line += 1);
	else if (*delim == 0x0)
		return (NULL);
	return (0);
}
