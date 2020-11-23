#include "minishell.h"

char	*pipeparser(char **line, char *delim, t_genlist *templist)
{
	templist->set->consq = *delim;
	//приделать новый лист
	templist->next = initial_genlist();
	return (*line += 1);
}