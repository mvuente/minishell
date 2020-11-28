#include "minishell.h"

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

	//printf("in cqprocessor item is %s\n", item);
	//printf("dolflag is %i\n", dolflag);
	if (dolflag)
	{
		if ((quot = ft_strchr(item, 0x22)) || (quot = ft_strchr(item, 0x27)))
		{
			start = quot;
			//printf("start is %s\n", start);
			finish = cqpars(&item, quot, *quot, all) - 1;
			finish = ft_memmove(finish, finish + 1, ft_strlen(finish + 1) + 1);//last
			start = (ft_memmove(start, start + 1, ft_strlen(start + 1) + 1)); //first
		}
	}
	return (item);
}
//
	//printf("after first memmove finish is %s\n", finish);
	//