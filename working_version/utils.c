/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 00:51:13 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/30 00:51:15 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_free_arr(char **arr)
{
	int		i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

t_set		*initial_set(void)
{
	t_set	*set;

	if (!(set = (t_set*)malloc(sizeof(t_set))))
		malloc_error();
	set->builtin = NULL;
	set->word = NULL;
	set->direct = NULL;
	set->spec = 0x0;
	set->consq = 0x0;
	set->fd[0] = 0;
	set->fd[1] = 0;
	return (set);
}

t_genlist	*initial_genlist(void)
{
	t_genlist	*genlist;

	if (!(genlist = (t_genlist*)malloc(sizeof(t_genlist))))
		malloc_error();
	genlist->set = initial_set();
	genlist->next = NULL;
	return (genlist);
}

char		*itemcrtr(char **line, char *finish, int dolflag, t_all all)
{
	char	*item;
	char	*dollar;
	char	*cqptr;
	char	*tmp;
	char	*quotset;

	quotset = "\"\'";
	if (!(item = ft_calloc(finish - *line + 1, sizeof(char))))
		malloc_error();
	item = ft_memmove(item, *line, finish - *line);
	cqptr = item;
	while (*cqptr != 0x0)
	{
		if (ft_strchr(quotset, *cqptr))
		{
			dolflag = 1;
			item = cqprocessor(item, &cqptr, dolflag, all);
		}
		else
		{
			cqptr++;
		}
	}
	*line = finish;
	return (item);
}

int		*pipe_init(void)
{
	int		fd[2];
	int		*tmp;

	fd[0] = 0;
	fd[1] = 1;
	tmp = fd;
	return (tmp);
}
