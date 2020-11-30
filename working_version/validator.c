/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:35:21 by mvuente           #+#    #+#             */
/*   Updated: 2020/11/30 21:35:42 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		no_operand_checker(char **line, char *delimiters)
{
	char	*tmp;

	tmp = *line + 1;
	while (*tmp != 0x0 && !ft_strchr(delimiters, *tmp))
	{
		if (*tmp != 0x20)
		{
			*line = tmp - 1;
			return (0x61);
		}
		tmp++;
	}
	return (0);
}

int		empty_checker(char *line, char *ptr)
{
	char	*tmp;

	tmp = line;
	while (tmp != ptr)
	{
		if (*tmp != 0x20)
			return (0x61);
		tmp++;
	}
	return (0);
}

int		empty_redirect_checker(char *line, char *delimiters)
{
	char	*tmp;

	tmp = line;
	while (*tmp != 0x0)
	{
		if (*tmp == 0x3c || *tmp == 0x3e)
		{
			if (*tmp == 0x3e && *(tmp + 1) == 0x3e)
				tmp++;
			if (!no_operand_checker(&tmp, delimiters))
				return (empt_dir_error());
		}
		tmp++;
	}
	return (0);
}

int		delim_checker(char *line, char *quotset)
{
	char	*tmp;
	char	*tempstring;

	tmp = line;
	tempstring = line;
	while (*tmp != 0x0)
	{
		if ((*tmp == 0x7c || *tmp == 0x3b) && !is_open_cqs(line, tmp, quotset))
		{
			if (*(tmp + 1) == *tmp)
				return (delim_error(tmp, 2));
			else if (!empty_checker(tempstring, tmp))
				return (delim_error(tmp, 1));
			tempstring = tmp + 1;
		}
		tmp++;
	}
	return (0);
}

int		validator(char *line, t_all *all)
{
	int		er;

	if ((er = delim_checker(line, all->quot)) ||
	(er = empty_redirect_checker(line, all->small_delim)))
		return (er);
	return (0);
}
