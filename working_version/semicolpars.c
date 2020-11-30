#include "minishell.h"

int		empty_checker(char *line, char *ptr)
{
	char	*tmp;

	tmp = line;
	while (tmp != ptr)
	{
		if (*tmp != 0x20)
			return (0x61);
		tmp++;
	}
	return (0);
}

int    delim_checker(char *line, char *quotset)
{
	char	*tmp;
	char	*tempstring;
	
	tmp = line;
	tempstring = line;
	while (*tmp != 0x0)
	{
		if ((*tmp == 0x7c || *tmp == 0x3b) && !is_open_cqs(line, tmp, quotset))
		{
			if (*(tmp + 1) == *tmp)
				return (delim_error(tmp, 2));
			else if (!empty_checker(tempstring, tmp))
				return (delim_error(tmp, 1));
			tempstring = tmp + 1;
		}
		tmp++;
	}
	return (0);
}

char	*semicolparser(char **line, t_genlist **genlist, t_all *all)
{
	t_genlist	*tmplist;
	int			pipecount;		

	tmplist = *genlist;
	while (tmplist->next)
		tmplist = tmplist->next;
	tmplist->set->consq = 0x3b;
	if ((pipecount = pipefinder(*genlist)))
    	ft_pipe(all, *genlist, pipecount);
	else
		executer(*genlist, all, 0);
	*genlist = initial_genlist();
	return (*line += 1);
}
