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

	finish = tmp;
	while (*finish != symb || *finish != 0x0)
		finish++;
	if (*finish == 0x0)
		command_error();
	finish = ft_memmove(finish, finish + 1, ft_strlen(finish + 1) + 1);//last
	tmp = (ft_memmove(tmp, tmp + 1, ft_strlen(tmp + 1) + 1)); //first
	return (finish - 1);	
}

void	reader(char *line, t_all all) //par of this func could be a parser function
{
    char		*tmp;
	char		*delimiters;
	char		*quot;
	int			*fd;
	t_genlist	*genlist;

	delimiters = ";|<> ";
	quot = "\"\'";
	genlist = initial_genlist();
	tmp = line;
	if (!(fd = (int*)malloc(sizeof(int) * 2)))
		malloc_error();
	fd[0] = 0;
	fd[1] = 1;
	//printf("fd started %i\n", fd[1]);
	while (*tmp != 0x0)// tokenazing starts
	{ 
		//printf("tmp is %p\n", tmp);
		//printf("line is %p\n", line);
		if (ft_strchr(quot, *tmp))
			tmp = cqpars(tmp, *tmp);
		else if (*tmp == 0x24)
			tmp = dollarpars(&line, tmp, all); // write this! to return ptr before delimiter
		else if (ft_strchr(delimiters, *tmp))
			tmp = tokencrtr(&line, tmp, &genlist, &fd); // to proceed the token and shift line pointer
		else
			tmp++;
		//if (*tmp == ';')
		//	executer(genlist);
		//else if (*tmp == '|')

	}
	tokencrtr(&line, tmp, &genlist, &fd);
	//printf("OK?\n");
	executer(genlist, &fd, &all);
}