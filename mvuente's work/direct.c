#include "minishell.h"

char	*dirpars(char **line, char *start, t_set *set)
{
	char	*tmp;

	while (*start == 0x3c || *start == 0x3e)
		start++;
	tmp = itemcrtr(line, start);
	if (!(ft_memcmp("<", tmp, 2)) || !(ft_memcmp(">", tmp, 2)) || !(ft_memcmp(">>", tmp, 3)))
		set->divider = lstaddfront(set->divider, tmp);
	else
		command_error();
	return (start);
}