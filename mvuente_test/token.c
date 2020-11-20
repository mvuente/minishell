#include "minishell.h"

char	*textpars(char **line, char *tmp, t_set *set)
{	
	//printf("textpasr started\n");
	*set = builtinrcrdr(itemcrtr(line, tmp), *set);
	return (tmp + 1);
}

char	*tokencrtr(char **line, char *delim, t_genlist **genlist, int **fd)
{
	char		*tmp;
	t_genlist	*templist;

	//printf("first fd[1] is %i\n", *(*fd + 1));
	//printf("first fd[0] is %i\n", **fd);
	templist = *genlist;
	while (templist->next)
		templist = templist->next;
	//printf("Am I here?\n");
	if (*line < delim)
	{
		//printf("tmp is %p\n", delim);
		//printf("line is %p\n", *line);
		return (textpars(line, delim, templist->set));
	}
	else if (*delim == 0x3c || *delim == 0x3e)
		{
			//printf("direct should be started\n");
			return (dirpars(line, delim, fd));
		}
	else if (*delim == 0x3b || *delim == 0x7c)
		{
			return (processpars(line, delim, &templist));
			//list = listoper(set, list); MAKE HERE!
			//line = delim + 1;
		}
	else if (*delim == 0x20)
		return (*line += 1);
	else if (*delim == 0x0)
		return (NULL);
}