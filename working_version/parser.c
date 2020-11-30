#include "minishell.h"

void	reader(char **line, t_all *all)
{
    char		*tmp;
	int			pipecount;
	t_genlist	*genlist;

	all->ptr_to_free = *line;
	if (validator(*line, all))
		return ;
	genlist = initial_genlist();
	tmp = *line;
	while (*tmp != 0x0)
	{ 
		if (ft_strchr(all->quot, *tmp))
		{
			if (!(tmp = cqpars(line, tmp, *tmp, all)))
				{
					cleargenlist(genlist);
					return ;
				}
		}
		else if (*tmp == 0x24 && *(tmp + 1) != 0x0 && *(tmp + 1) != 0x20 &&
				*(tmp + 1) != 0x3b && *(tmp + 1) != 0x7c)
			tmp = dollarpars(line, tmp, all);
		else if (ft_strchr(all->delimiters, *tmp))
			tmp = tokencrtr(line, tmp, &genlist, all);
		else
			tmp++;
	}
	if (*line != tmp)
		tokencrtr(line, tmp, &genlist, all);
	if ((pipecount = pipefinder(genlist)))
    	ft_pipe(all, genlist, pipecount);
	else if (**line == 0x0 && *(*line - 1) != 0x3b)
		executer(genlist, all, 0);
	cleargenlist(genlist);
	return ;
}