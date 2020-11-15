#include "minishell.h"

char	*dirpars(char **line, char *start, int **fd)
{
	char		*tmp;
	char		*delimiters;
	char		*quot;
	char		*direct;

	delimiters = ";|<> ";
	quot = "\"\'";

	while (*start == 0x3c || *start == 0x3e)
		start++;
	direct = itemcrtr(line, start);
	printf("%s\n", direct);
	if (ft_memcmp("<", direct, 2) && ft_memcmp(">", direct, 2) && ft_memcmp(">>", direct, 3))
		command_error();
	tmp = start;
	while (*tmp != 0x0)
	{
		if (*tmp == 0x20)
			tmp++;
		else
			break;
	}
	*line = tmp;
	while (*tmp != 0x0 && !ft_strchr(delimiters, *tmp))
	{ 
		//printf("in 1-st loop\n");
		if (ft_strchr(quot, *tmp))
			tmp = cqpars(tmp, *tmp);
		else
			tmp++;
	}
		dir_exec(fd, direct, itemcrtr(line, tmp));
	return (tmp);
} 