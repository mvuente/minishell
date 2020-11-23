#include "minishell.h"

//char	*backpars(char *tmp)
//{
//	if (*(tmp + 1) == 0x0)
//		command_error();
//	return (ft_memmove(tmp, tmp + 1, ft_strlen(tmp + 1) + 1) + 1);
//}

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
	finish = ft_memmove(finish, finish + 1, ft_strlen(finish + 1) + 1);//last
	//printf("after first memmove finish is %s\n", finish);
	tmp = (ft_memmove(tmp, tmp + 1, ft_strlen(tmp + 1) + 1)); //first
	return (finish - 1);	
}

void	reader(char *line, t_all all) //par of this func could be a parser function
{
    char		*tmp;
	char		*delimiters;
	char		*quot;
	int			pipecount;
	int			*fd;
	t_genlist	*genlist;

	//printf("beginning: %s\n", line);
	delimiters = ";|<> ";
	quot = "\"\'";
	genlist = initial_genlist();
	tmp = line;
	if (!(fd = (int*)malloc(sizeof(int) * 3)))
		malloc_error();
	fd[0] = 0;
	fd[1] = 1;
	fd[2] = 2;
	//printf("fd started %i\n", fd[1]);
	while (*tmp != 0x0)// tokenazing starts
	{ 
		//printf("tmp is %p\n", tmp);
		//printf("line is %p\n", line);
		if (ft_strchr(quot, *tmp))
		{
			//printf("before quotes is %s\n", tmp);
			tmp = cqpars(tmp, *tmp);
		}
		else if (*tmp == 0x24)
			tmp = dollarpars(&line, tmp, all); // write this! to return ptr before delimiter
		else if (ft_strchr(delimiters, *tmp))
			tmp = tokencrtr(&line, tmp, &genlist, &fd, &all); // to proceed the token and shift line pointer
		else
			tmp++;
		//if (*tmp == ';')
		//	executer(genlist);
		//else if (*tmp == '|')

	}
	tokencrtr(&line, tmp, &genlist, &fd, &all);
	if (pipecount = pipefinder(genlist))
    	ft_pipe(&all, genlist, pipecount, &fd);
	else
		executer(genlist, &fd, &all);
	
}