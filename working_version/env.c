/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:27:35 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/25 10:32:35 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write_env(t_env *bufenv, int fd)
{
	while (bufenv)
	{
		if (bufenv->data)
		{
			ft_putstr_fd(bufenv->name, fd);
			ft_putchar_fd('=', fd);
			ft_putendl_fd(bufenv->data, fd);
		}
		bufenv = bufenv->next;
	}
}

int		ft_check_word_env(char *word)
{
	if (!(ft_strchr(word, '=')))
	{
		ft_putstr_fd("env:", 2);
		ft_putstr_fd(word, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	return (0);
}

int	env_executer(t_set *set, t_all *all)
{
	int		check;

	check = 0;
	if (!set->word)
		ft_write_env(all->myenv, 1);// *fd[1], fd); //ВЫЗЫВАЕМАЯ Ф-ЦИЯ БЕРЕТ ТОЛЬКО ДВА ПАРАМЕТРА (ДУМАЮ, ЧТ fd ей вообще не нужен)
	if (set->word)
	{
		check = ft_check_word_env(set->word->word);
		while (set->word && check == 0)
		{
			if (ft_check_word_env(set->word->word))
				ft_putstr_fd(set->word->word, 1);
			else
			{
				ft_putstr_fd("env:", 2);
				ft_putstr_fd(set->word->word, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				check = 127;
			}
			set->word = set->word->next;
		}
	}
	return (check);
}
