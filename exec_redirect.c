/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:57:19 by mvuente           #+#    #+#             */
/*   Updated: 2020/11/30 21:57:22 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_error(int fd, t_dirlist *tmp, t_all *all)
{
	fd = 0;
	ft_putstr_fd("bash_na_bash: ", 2);
	ft_putstr_fd(tmp->fname, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	all->fdstat = 1;
	return ;
}

void	closer(int *fd, t_dirlist *tmp)
{
	if (fd[0] && *tmp->direct == 0x3c)
		close(fd[0]);
	else if (fd[1] != 1 && *tmp->direct == 0x3e)
		close(fd[1]);
	return ;
}

void	dir_exec(int *fd, t_dirlist *direct, t_all *all)
{
	t_dirlist	*tmp;

	all->fdstat = 0;
	tmp = direct;
	dup2(0, fd[0]);
	dup2(1, fd[1]);
	while (tmp)
	{
		closer(fd, tmp);
		if (*tmp->direct == 0x3c)
		{
			if ((fd[0] = open(tmp->fname, O_RDWR)) == -1)
				open_error(fd[0], tmp, all);
			dup2(fd[0], 0);
		}
		else if (!ft_memcmp(">", tmp->direct, 2))
			fd[1] = open(tmp->fname, O_RDWR | O_CREAT, S_IRWXU);
		else
			fd[1] = open(tmp->fname, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
		dup2(fd[1], 1);
		tmp = tmp->next;
	}
	return ;
}
