/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 01:00:15 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/30 01:00:17 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_all *all)
{
	char	dir[500];
	int		descr;

	descr = 0;
	getcwd(dir, 500);
	ft_putendl_fd(dir, 1);
	dup2(1, descr);
	close(descr);
	dup2(all->fd_1, 1);
	errno = 0;
}
