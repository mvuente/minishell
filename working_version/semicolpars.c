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

	//printf("or here?\n");
	tmplist = *genlist;
	//tmplist->set->consq = 0x3b;
	while (tmplist->next)
		tmplist = tmplist->next;
	tmplist->set->consq = 0x3b;
	// hereby I need to make a list of comand
	if ((pipecount = pipefinder(*genlist)))
    	ft_pipe(all, *genlist, pipecount);
	else
		executer(*genlist, all, 0);
	//cleargenlist(*genlist);
	//printf("I'm here?\n");
	*genlist = initial_genlist();
	return (*line += 1);
}


// below is for training

//char	*pipeparser(char **line, char *delim, t_genlist *templist)
//{
//	templist->set->consq = *delim;
	//приделать новый лист
//	templist->next = initial_genlist();
//	return (*line += 1);
//}

//int		pipefinder(t_genlist *genlist)
//{
//	t_genlist	*temp;
//	int			pipecount;
//
//	temp = genlist;
//	pipecount = 0;
//	while (temp)
//	{
//		if (temp->set->consq == 0x7c)
//			pipecount++;
//		temp = temp->next;
//	}
//	return (pipecount);
//}