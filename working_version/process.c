#include "minishell.h"

char	*processpars(char **line, char *delim, t_genlist **genlist)
{
	genlstadd(delim, genlist);
	*line = delim + 1;
	return (delim + 1);
}
