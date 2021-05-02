/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:44:33 by mvuente           #+#    #+#             */
/*   Updated: 2020/11/30 21:44:39 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*processpars(char **line, char *delim, t_genlist **genlist)
{
	genlstadd(delim, genlist);
	*line = delim + 1;
	return (delim + 1);
}
