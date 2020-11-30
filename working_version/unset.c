/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:55:03 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/29 16:31:56 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_no_valid_word_unset(char *word)
{
	ft_putstr_fd("bash_na_bash: unset: `", 2);
	ft_putstr_fd(word, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int		ft_delete_env(char *str, t_env *bufenv, int flag)
{
	int		i;
	t_env	*tmp;
	void	*ptr;

	i = ft_strlen(str);
	while (bufenv)
	{
		if (!(ft_strncmp(bufenv->name, str, i)) && i == ft_strlen(bufenv->name))
		{
			flag = 1;
			tmp->next = bufenv->next;
			free(bufenv->data);
			free(bufenv->name);
			free(bufenv);
		}
		if (flag == 1)
			break ;
		tmp = bufenv;
		bufenv = bufenv->next;
	}
	if (flag == 0)
		return (1);
	return (0);
}

int		ft_check_word_unset(char *word)
{
	int		i;
	char	c;
	int		flag;

	flag = 0;
	i = -1;
	if (word[0] >= '0' && word[0] <= '9')
		return (1);
	while (word[++i])
	{
		c = word[i];
		if ((c >= '*' && c <= '/') || (c >= ':' && c <= '@') || \
				(c >= '{' && c <= '~'))
			return (1);
	}
	return (0);
}

int		unset_executer(t_set *set, t_all *all)
{
	int		check;
	int		flag;
	t_list	*tmp;

	tmp = set->word;
	flag = 0;
	if (!ft_check_258(set, all))
		return (258);
	while (tmp)
	{
		check = ft_check_word_unset(tmp->word);
		if (check == 1)
		{
			ft_no_valid_word_unset(tmp->word);
			all->error = 1;
			flag = 1;
		}
		else
			ft_delete_env(tmp->word, all->myenv, 0);
		tmp = tmp->next;
	}
	if (flag == 1)
		return (1);
	return (0);
}
