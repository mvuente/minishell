#include "minishell.h"

char	*textpars(char **line, char *tmp, t_set *set)
{	
	printf("textpasr started\n");
	*set = builtinrcrdr(itemcrtr(line, tmp), *set);
	return (tmp + 1);
}

char	*tokencrtr(char **line, char *delim, t_genlist **genlist)
{
	char		*tmp;
	t_genlist	*templist;

	templist = *genlist;
	while (templist->next)
		templist = templist->next;
	if (*line != delim)
		return (textpars(line, delim, templist->set));
	else if (*delim == 0x3c || *delim == 0x3e)
		{
			return (dirpars(line, delim, templist->set)); // ready
		}
	else if (*delim == 0x3b || *delim == 0x7c)
		{
			return (processpars(line, delim, &templist));
			//list = listoper(set, list); MAKE HERE!
			//line = delim + 1;
		}
	else if (*delim == 0x20)
		return (*line += 1);
}