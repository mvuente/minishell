#include "minishell.h"

char	*cqpars(char *tmp, char symb) //check for \ in ""
{
	char	*finish;

	finish = tmp + 1;
	//printf("finish is %s\n", finish);	
	//printf("cqpars started\n");
	while (*finish != symb && *finish != 0x0)
		finish++;
	if (*finish == 0x0)
		command_error();
	//printf("before first memmove finish is %s\n", finish);
	
	return (finish + 1);	
}

char	*cqprocessor(char *item)
{
	char	*quot;
	char	*start;
	char	*finish;

	if ((quot = ft_strchr(item, 0x22)) || (quot = ft_strchr(item, 0x27)))
	{
		start = quot;
		printf("start is %s\n", start);
		finish = cqpars(quot, *quot) - 1;
		finish = ft_memmove(finish, finish + 1, ft_strlen(finish + 1) + 1);//last
		start = (ft_memmove(start, start + 1, ft_strlen(start + 1) + 1)); //first
	}
	return (item);
}
//
	//printf("after first memmove finish is %s\n", finish);
	//