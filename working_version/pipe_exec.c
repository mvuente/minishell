/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 16:10:07 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/29 16:17:32 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_lstsize_pipes(t_genlist *lst)
{
	int		i;

	if (!lst)
		return (0);
	i = 1;
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int		ft_work_pipe(t_all *all, t_genlist *pipes, int size, int pipefd[2])
{
	pid_t	cpid;

	if ((cpid = fork()) == -1)
		return (1);
	if (cpid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		//if (pipes->set->direct)
		//	dir_exec(pipe_init(), pipes->set->direct);
		executer(pipes, all, 1);
		close(pipefd[1]);
		exit(0);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		waitpid(cpid, 0, WUNTRACED);
		pipes = pipes->next;
		if (size < 1)
			executer(pipes, all, 0);
		close(pipefd[0]);
	}
	return (0);
}

int		ft_pipe(t_all *all, t_genlist *pipes, int size)
{
	int		pipefd[2];
	pid_t	cpid;

	size--;
	while (size >= 0)
	{
		if (pipe(pipefd) == -1)
			return (0);
		ft_work_pipe(all, pipes, size, pipefd);
		size--;
		pipes = pipes->next;
	}
	return (0);
}
