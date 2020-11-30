#include "minishell.h"

int		no_operand_checker(char **line, char *delimiters)
{
	char	*tmp;

	tmp = *line + 1;
	while (*tmp != 0x0 && !ft_strchr(delimiters, *tmp))
	{
		if (*tmp != 0x20)
		{
			*line = tmp - 1;
			return (0x61);
		}
		tmp++;
	}
	return (0);
}

int    empty_redirect_checker(char *line, char *delimiters)
{
	char	*tmp;
	//char	*tempstring;
	
	tmp = line;
	//tempstring = line;
	while (*tmp != 0x0)
	{
		if (*tmp == 0x3c || *tmp == 0x3e)
		{
			if (*tmp == 0x3e && *(tmp + 1) == 0x3e)
				tmp++;
			if (!no_operand_checker(&tmp, delimiters))
				return (empt_dir_error());
			//tempstring = tmp + 1;
		}
		tmp++;
	}
	return (0);
}

t_dirlist	*dir_record(t_set *set, char *direct, char *operand)
{
	t_dirlist	*tmp;

	if (*operand == 0x0)

	tmp = set->direct;
	if (!tmp)
		return (dirlistcrtr(direct, operand));
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = dirlistcrtr(direct, operand);
	return (set->direct);
}

char	*dirpars(char **line, char *start, t_set *set, t_all *all)
{
	char		*tmp;
	char		*delimiters;
	char		*quot;
	char		*direct;

	delimiters = ";|<> ";
	quot = "\"\'";

	while (*start == 0x3c || *start == 0x3e)
		start++;
	direct = itemcrtr(line, start, 0, *all);
	//printf("%s\n", direct);
	if (ft_memcmp("<", direct, 2) && ft_memcmp(">", direct, 2) && ft_memcmp(">>", direct, 3))
		command_error(); // что считать ошибкой?????
	tmp = start;  // до строки 80 кусок повторяется выше
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
			tmp = cqpars(line, tmp, *tmp, all);
		else
			tmp++;
	}
	printf("tmp is %s\n", tmp);
	set->direct = dir_record(set, direct, itemcrtr(line, tmp, 1, *all));
	return (tmp);
} 