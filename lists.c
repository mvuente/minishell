/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:47:49 by mvuente           #+#    #+#             */
/*   Updated: 2020/11/30 21:47:51 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dirlist	*dirlistcrtr(char *direction, char *fname)
{
	t_dirlist	*direct;

	if (!(direct = (t_dirlist*)malloc(sizeof(t_dirlist))))
		malloc_error();
	direct->direct = direction;
	direct->fname = fname;
	direct->next = NULL;
	return (direct);
}
