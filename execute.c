/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:50:22 by mvuente           #+#    #+#             */
/*   Updated: 2020/11/30 21:50:26 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		echo_executer(t_set *set, t_all *all)
{
	int			descr;
	t_list		*tmp;

	descr = 0;
	tmp = set->word;
	if (tmp)
	{
		write(1, tmp->word, ft_strlen(tmp->word));
		tmp = tmp->next;
	}
	while (tmp)
	{
		write(1, " ", 1);
		write(1, tmp->word, ft_strlen(tmp->word));
		tmp = tmp->next;
	}
	if (!set->spec)
		write(1, "\n", 1);
	dup2(1, descr);
	if (descr != 1)
		close(descr);
	dup2(all->fd_1, 1);
	errno = 0;
}

void		exe_pars(t_genlist *tmp, t_all *all)
{
	if (!ft_memcmp(tmp->set->builtin, "pwd", 4))
		ft_pwd(all);
	else if (!ft_memcmp(tmp->set->builtin, "echo", 5))
		echo_executer(tmp->set, all);
	else if (!ft_memcmp(tmp->set->builtin, "export", 7))
		errno = export_executer(tmp->set, all);
	else if (!ft_memcmp(tmp->set->builtin, "cd", 3))
		errno = ft_cd(all, tmp->set);
	else if (!ft_memcmp(tmp->set->builtin, "env", 4))
		errno = env_executer(tmp->set, all);
	else if (!ft_memcmp(tmp->set->builtin, "unset", 6))
		errno = unset_executer(tmp->set, all);
	else if (!ft_memcmp(tmp->set->builtin, "exit", 5))
		errno = ft_exit(all, tmp->set);
	else
		errno = ft_syscall(all, tmp->set, all->myenv);
	return ;
}

void		executer(t_genlist *genlist, t_all *all, int pipe_flag)
{
	t_genlist	*tmp;

	tmp = genlist;
	if (tmp->set->direct)
	{
		dir_exec(pipe_init(), tmp->set->direct, all);
		if (all->fdstat)
		{
			errno = 1;
			return ;
		}
	}
	if (tmp->set->builtin)
		exe_pars(tmp, all);
	if (!pipe_flag)
		dup2(all->fd_0, 0);
	dup2(all->fd_1, 1);
	return ;
}
