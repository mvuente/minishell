#include "minishell.h"

//char	*backpars(char *tmp)
//{
//	if (*(tmp + 1) == 0x0)
//		command_error();
//	return (ft_memmove(tmp, tmp + 1, ft_strlen(tmp + 1) + 1) + 1);
//}


void	reader(char *line, t_all all) //par of this func could be a parser functio 
{
    char		*tmp;
	char		*delimiters;
	char		*quot;
	int			pipecount;
	//int			*fd;
	t_genlist	*genlist;

	//printf("beginning: %s\n", line);
	if (delim_checker(line))
		return ;
	delimiters = ";|<> ";
	quot = "\"\'";
	genlist = initial_genlist();
	tmp = line;
	//if (!(fd = (int*)malloc(sizeof(int) * 3)))
	//	malloc_error();
	//fd[0] = 0;
	//fd[1] = 1;
	//fd[2] = 2;
	//printf("fd started %i\n", fd[1]);
	while (*tmp != 0x0)// tokenazing starts
	{ 
		//printf("tmp is %p\n", tmp);
		//printf("line is %p\n", line);
		if (ft_strchr(quot, *tmp))
		{
			//printf("before quotes is %s\n", tmp);
			tmp = cqpars(tmp, *tmp); // just to find the end of quotes and move the pointer there to
		}
		else if (*tmp == 0x24)
			tmp = dollarpars(&line, tmp, all); // write this! to return ptr before delimiter
		else if (ft_strchr(delimiters, *tmp))
			tmp = tokencrtr(&line, tmp, &genlist, &all); // to proceed the token and shift line pointer
		else
			tmp++;
		//if (*tmp == ';')
		//	executer(genlist);
		//else if (*tmp == '|')

	}
	tokencrtr(&line, tmp, &genlist, &all);
	if ((pipecount = pipefinder(genlist)))
    	ft_pipe(&all, genlist, pipecount);
	//else if (genlist->set->direct)
	//{
	//	executer(genlist, dir_exec(pipe_init(), genlist->set->direct), &all);
	//}
	else
		executer(genlist, &all, 0);
}