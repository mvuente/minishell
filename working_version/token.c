#include "minishell.h"

char	*textpars(char **line, char *tmp, t_set *set, t_all all)
{	
//	printf("textpasr started and *line is %s\n", *line);

	*set = builtinrcrdr(itemcrtr(line, tmp, 0, all), *set);
	return (tmp);
}

char	*tokencrtr(char **line, char *delim, t_genlist **genlist, t_all *all)
{
	char		*tmp;
	t_genlist	*templist;

	//printf("first fd[1] is %i\n", *(*fd + 1));
//	printf("token started\n");
	templist = *genlist;
	while (templist->next)
		templist = templist->next;
	//printf("Am I here?\n");
	if (*line < delim)
	{
		//printf("tmp is%s\n", delim);
		//printf("line is%s\n", *line);
		return (textpars(line, delim, templist->set, *all));
	}
	else if (*delim == 0x7c)
		{
			return (pipeparser(line, delim, templist));
		}
	else if (*delim == 0x3b)
		{
			//printf("found semicolons?\n");
			//printf("line is %s\n", *line);
			//printf("tmp is %s\n", delim);
			return (semicolparser(line, genlist, all));
		}
	else if (*delim == 0x3c || *delim == 0x3e)
		{
			//printf("direct should be started\n");
			return (dirpars(line, delim, templist->set, *all));
		}
	//else if (*delim == 0x3b || *delim == 0x7c)
	//	{
	//		return (processpars(line, delim, &templist));
			//list = listoper(set, list); MAKE HERE!
			//line = delim + 1;
	//	}
	else if (*delim == 0x20)
		return (*line += 1);
	else if (*delim == 0x0)
		return (NULL);
	return (0);
}