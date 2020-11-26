/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:17:52 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/25 10:23:23 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write_exit(char *word, int fd)
{
	ft_putstr_fd("e_bash: exit: ", fd);
	ft_putstr_fd(word, fd);
	ft_putendl_fd(": numeric argument required", fd);//выходит
	exit(255);
}

int	ft_exit(t_all *all, t_set *set, int *fd) // НУЖЕН ЛИ FD???
{
	int		i;

	if (!set->word)
		exit(0);
	if (ft_strchr(&set->consq, '|'))//// подумать куда пайп положить и что с ним
		//return (0);
		return (0);
	//arr = ft_split(set->builtin, ' '); //СТРОКИ 20, 25 И 33 МОЖЕТ НЕ НУЖНЫ... АРГУМЕНТЫ ЛЕЖАТ В СПИСКЕ SET->WORD
	i = -1;
	while(set->word->word[++i])
	{
	if (set->word->word[i] < '0'  || set->word->word[i] > '9')
		ft_write_exit(set->word->word, 2);//ПРИ НЕОБХОДИМОСТИ ЗАМЕНИТЬ 1 НА АКТУАЛЬНЫЙ FD
	}
	if (set->word->next)
	{
		ft_putendl_fd("e_bash: exit: too many arguments", 2);// не выходит ПРИ НЕОБХОДИМОСТИ ЗАМЕНИТЬ 1 НА АКТУАЛЬНЫЙ FD
		//all->error = 1;
		return (1);
	}
    //if (set->builtin)
      //  all->error = ft_atoi(set->builtin);
	all->error = ft_atoi(set->word->word) % 256;
	exit(all->error);
	//return (0);
}
