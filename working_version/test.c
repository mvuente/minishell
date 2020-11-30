/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:17:45 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/30 11:17:47 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigl(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\b\b  \b\b", 6);
		if (g_flag == 1)
		{
			errno = 130;
			ft_putendl_fd("^C", 1);
		}
		else
		{
			ft_putstr_fd("\nbash_na_bash! ", 1);
			errno = 1;
		}
	}
	if (sig == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
		if (g_flag == 1)
		{
			ft_putendl_fd("^\\Quit: 3", 1);
			errno = 131;
			return ;
		}
	}
}

void	ft_init_all(t_all *all, char **env, t_env *bufenv)
{
	all->fd_0 = dup(0);
	all->fd_1 = dup(1);
	ft_creat_env(env, &bufenv);
	all->myenv = bufenv;
	if (!(all->home = ft_strdup(ft_get_value(bufenv, "HOME"))))
		malloc_error();
	g_flag = 0;
	all->delimiters = ";|<> ";
	all->quot = "\"\'";
	all->ptr_to_free = NULL;
	signal(SIGINT, ft_sigl);
	signal(SIGQUIT, ft_sigl);
}

int		main(int argc, char *argv[], char *env[])
{
	t_env	*bufenv;
	t_all	all;

	ft_init_all(&all, env, bufenv);
	minishell(all);
	return (0);
}
