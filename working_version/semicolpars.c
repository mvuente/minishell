#include "minishell.h"

char	*semicolparser(char **line, int **fd, t_genlist **genlist, t_all *all)
{
	t_genlist	*tmplist;

	printf("or here?\n");
	tmplist = *genlist;
	while (tmplist->next)
		tmplist = tmplist->next;
	tmplist->set->consq = 0x3b;
	executer(*genlist, *fd, all);
	cleargenlist(*genlist);
	printf("I'm here?\n");
	*genlist = initial_genlist();
	return (*line += 1);
}