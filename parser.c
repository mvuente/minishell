#include "minishell.h"

char	*backpars(char *tmp)
{
	if (*(tmp + 1) == 0x0)
		command_error();
	return (ft_memmove(tmp, tmp + 1, ft_strlen(tmp + 1) + 1) + 1);
}

char	*cqpars(char *tmp, char symb)
{
	char	*finish;

	finish = tmp;
	while (*finish != symb || *finish != 0x0)
		finish++;
	if (*finish == 0x0)
		command_error();
	finish = ft_memmove(finish, finish + 1, ft_strlen(finish + 1) + 1);//last
	tmp = (ft_memmove(tmp, tmp + 1, ft_strlen(tmp + 1) + 1)); //first
	return (finish);	
}

char	*textpars(char **line, char *tmp)
{
	char	*item;

	if (!(item = ft_calloc(tmp - *line + 2, size0f(char))))
		malloc_error;
	item = ft_memmove(item, *line, tmp - *line + 1);
	*line = tmp;
	return (item);
}

t_set	**parser(char *line)
{
    char	*tmp;
	char	*item;
	char	cqflag;

	tmp = line;
	cqflag = 0x0;
	while (*tmp != 0x3c && *tmp != 0x3e && *tmp != 0x3b && *tmp != 0x7c &&
		*tmp != 0x20)
	{
		if (*tmp == 0x5c)
			tmp = backpars(tmp);
		else if ((*tmp == 0x22 || *tmp == 0x27) && !cgflag)
		{ 
			cqflag = 0x1;
			tmp = cqpars(tmp, *tmp);
		}
		else
			tmp++;
	}
	item = textpars(&line, tmp); // write this!
	// check for space <>>> and ; | separately
}