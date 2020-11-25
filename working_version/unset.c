/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:55:03 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/25 13:56:48 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_no_valid_word_unset(char *word)
{
	ft_putstr_fd("bash: unset: `", 1);
	ft_putstr_fd(word, 1);
	ft_putstr_fd("': not a valid identifier\n", 1);
}

int		ft_delete_env(char *str, t_env *bufenv, int flag)
{
	int		i;
	t_env	*tmp;
	void	*ptr;

	i = ft_strlen(str);
	while (bufenv->next)
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

void	ft_write_258(char *word)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 1);
	ft_putstr_fd(word, 1);
	ft_putendl_fd("'", 1);
}

int		f_check_258(t_set *set, t_all *all) /// ee можно добавить в общие ее использует unset
{
	t_list	*tmp;

	tmp = set->word;
	while (tmp)
	{
		if (ft_strchr(tmp->word, '(') || ft_strchr(tmp->word, ')'))
		{
			if (tmp->word[0] == '(' && !tmp->word[1])
				ft_putendl_fd(\
						"bash: syntax error near unexpected token `newline'", 1);
			else if (tmp->word[0] == '(' && tmp->word[1])
				ft_write_258(++tmp->word);
			else if (ft_strchr(tmp->word, '('))
				ft_putendl_fd("bash: syntax error near unexpected token `('"\
						, 1);
			else if (ft_strchr(tmp->word, ')'))
				ft_putendl_fd("bash: syntax error near unexpected token `)'"\
						, 1);
			all->error = 258;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	unset_executer(t_set *set, int *fd, t_all *all) // FD НЕ НУЖЕН???     не удаляет мои переменные
{
	int		check;
	int		flag;

	flag = 0;
	if (!f_check_258(set, all))
		return ;
		//return (258);
	while (set->word)
	{
		check = ft_check_word_unset(set->word->word);//заменить на ft_check
		if (check == 1)
		{
			ft_no_valid_word_unset(set->word->word);
			all->error = 1;
			flag = 1;
		}
		else
			ft_delete_env(set->word->word, all->myenv, 0);
		set->word = set->word->next;
	}
	if (flag == 1)
		return ;
		//return (1);
	return ;
	//return (0);
}
