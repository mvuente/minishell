#include "minishell.h"

char	*closest_cq(char *line, char cq)
{
	char	*ptr;

	ptr = line;
	while (*ptr != 0x0)
	{
		if (*ptr == cq)
			return (ptr);
		ptr++;
	}
	return (NULL);
}

int		is_open_cqs(char *line, char *delimiter, char *quotset)
{
	char	*ptr;
	char	*closest;

	
	//printf("delimiter is %s\n", delimiter);
	if (*delimiter != 0x7c && *delimiter != 0x3b)
		return (2);
	//printf("test\n");
	ptr = line;
	//printf("line is %s\n", line);
	while (*ptr != 0x0)
	{
		if (ft_strchr(quotset, *ptr) && ptr < delimiter &&
		(closest = closest_cq(ptr + 1, *ptr)) && closest > delimiter)
			return (1);
		ptr++;
	}
	return (0);
}

char	*cqpars(char **line, char *tmp, char symb, t_all all) //check for \ in ""
{
	char	*finish;
	int		finflag;

	finflag = 0;
	finish = tmp + 1;
	//printf("finish is %s\n", finish);	
	//printf("cqpars started\n");
	while (*finish != symb && *finish != 0x0 && !finflag)
	{
		if (*finish == 0x24 && symb == 0x22)
		{
			finish = dollarpars(line, finish, all);// доллар надо заменить раскрытой переменной, если кавычки двойные
			//printf("finish is %s\n", finish);
			//printf("string after dollar insite quotes is %s\n", *line);
			//printf("before finish is %s\n", finish - 1);
			finflag = 1;
		}
		finish++;
	}
	if (*finish == 0x0 && !finflag)
		command_error();
	//printf("before first memmove finish is %s\n", finish);
	if (finflag)
		finish--;
	return (finish + 1);	
}

char	*cqprocessor(char *item, int dolflag, t_all all)
{
	char	*quot;
	char	*start;
	char	*finish;
	char	*quotset;
	char	*tmp;

	printf("in cqprocessor item is %s\n", item);
	//printf("dolflag is %i\n", dolflag);
	quotset = "\"\'";
	if (dolflag)
	{
		tmp = item;
		while (*tmp != 0)
		{
			printf("pointer in an analising string is %c\n", *tmp);
			if (ft_strchr(quotset, *tmp))
			{
				quot = tmp;
				start = tmp;
				printf("start is %s\n", start);
				finish = cqpars(&tmp, quot, *quot, all) - 1;
				finish = ft_memmove(finish, finish + 1, ft_strlen(finish + 1) + 1);//last
				start = (ft_memmove(start, start + 1, ft_strlen(start + 1) + 1)); //first
				break;
			}
			tmp++;
		}
	}
	return (item);
}
//
	//printf("after first memmove finish is %s\n", finish);
	//