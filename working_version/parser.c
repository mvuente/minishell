#include "minishell.h"

void	pre_exec(char **line, t_genlist *genlist, t_all *all)
{
	int	pipecount;

	if ((pipecount = pipefinder(genlist)))
    	ft_pipe(all, genlist, pipecount);
	else if (**line == 0x0 && *(*line - 1) != 0x3b)
		executer(genlist, all, 0);
	return ;
}

char	*real_parser(char **line, char *tmp, t_all *all, t_genlist *genlist)
{
	if (ft_strchr(all->quot, *tmp))
		tmp = cqpars(line, tmp, *tmp, all);
	else if (*tmp == 0x24 && *(tmp + 1) != 0x0 && *(tmp + 1) != 0x20 &&
		*(tmp + 1) != 0x3b && *(tmp + 1) != 0x7c)
		tmp = dollarpars(line, tmp, all);
	else if (ft_strchr(all->delimiters, *tmp))
		tmp = tokencrtr(line, tmp, &genlist, all);
	else
		tmp++;
	return (tmp);
}

void	reader(char **line, t_all *all)
{
    char		*tmp;
	t_genlist	*genlist;

	all->ptr_to_free = *line;
	if (validator(*line, all))
		return ;
	genlist = initial_genlist();
	tmp = *line;
	while (*tmp != 0x0)
	{ 
		if (!(tmp = real_parser(line, tmp, all, genlist)))
		{
			cleargenlist(genlist);
			return ;
		}
	}
	tokencrtr(line, tmp, &genlist, all);
	pre_exec(line, genlist, all);
	cleargenlist(genlist);
	return ;
}