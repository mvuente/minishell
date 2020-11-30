/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 00:46:11 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/30 00:46:15 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_data(t_env *tmp, int flag, char *str)
{
	flag = 1;
	free(tmp->data);
	tmp->data = NULL;
	if (!(tmp->data = ft_strdup((ft_strchr(str, '=') + 1))))
		malloc_error();
}

void	ft_free_set(t_set *set)
{
	t_list		*tmp;
	t_list		*todie;
	t_dirlist	*dirtmp;
	t_dirlist	*dirtodie;

	tmp = set->word;
	while (tmp)
	{
		todie = tmp;
		free(tmp->word);
		free(todie);
		tmp = tmp->next;
	}
	dirtmp = set->direct;
	while (dirtmp)
	{
		dirtodie = dirtmp;
		free(dirtmp->direct);
		free(dirtmp->fname);
		dirtmp = dirtmp->next;
		free(dirtodie);
	}
	if (set->builtin)
		free(set->builtin);
	free(set);
}

void	cleargenlist(t_genlist *genlist)
{
	t_genlist	*templist;
	t_genlist	*tmp;

	templist = genlist;
	while (templist)
	{
		tmp = templist;
		ft_free_set(templist->set);
		templist = templist->next;
		free(tmp);
	}
	return ;
}

void	ft_write_258(char *word)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(word, 2);
	ft_putendl_fd("'", 2);
}

int		ft_check_258(t_set *set, t_all *all)
{
	t_list	*tmp;

	tmp = set->word;
	while (tmp)
	{
		if (ft_strchr(tmp->word, '(') || ft_strchr(tmp->word, ')'))
		{
			if (tmp->word[0] == '(' && !tmp->word[1])
				ft_putendl_fd(\
					"bash: syntax error near unexpected token `newline'", 2);
			else if (tmp->word[0] == '(' && tmp->word[1])
				ft_write_258(++tmp->word);
			else if (ft_strchr(tmp->word, '('))
				ft_putendl_fd("bash: syntax error near unexpected token `('"\
						, 2);
			else if (ft_strchr(tmp->word, ')'))
				ft_putendl_fd("bash: syntax error near unexpected token `)'"\
						, 2);
			all->error = 258;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
