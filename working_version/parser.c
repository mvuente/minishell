#include "minishell.h"

//char	*backpars(char *tmp)
//{
//	if (*(tmp + 1) == 0x0)
//		command_error();
//	return (ft_memmove(tmp, tmp + 1, ft_strlen(tmp + 1) + 1) + 1);
//}


void	reader(char **line, t_all all) //par of this func could be a parser functio 
{
    char		*tmp;
	char		*delimiters;
	char		*quot;
	int			pipecount;
	//int			quotflag;
	t_genlist	*genlist;

	//printf("beginning: %s\n", line);
	delimiters = ";|<> ";
	quot = "\"\'";
	if (delim_checker(*line, quot))
		return ;
	genlist = initial_genlist();
	printf("genlist allocated is %p\n", genlist);
	tmp = *line;
	//quotflag = 0;
	while (*tmp != 0x0)// tokenazing starts
	{ 
		//printf("tmp is %p\n", tmp);
		//printf("line is %p\n", line);
		if (ft_strchr(quot, *tmp))
		{
		//	if (*tmp == 0x27)
		//		quotflag = 1;
			//printf("before quuotes we have command %s\n", genlist->set->builtin);
			tmp = cqpars(line, tmp, *tmp, all); // just to find the end of quotes and move the pointer there to
			//printf("IN PARSER: %s\n", tmp);
		//	printf("IN PARSER: %s\n", line);
		}
		
		else if (*tmp == 0x24 && *(tmp + 1) != 0x0 && *(tmp + 1) != 0x20 &&
				*(tmp + 1) != 0x3b && *(tmp + 1) != 0x7c)// && !quotflag)
		{
			//printf("how many?\n");
			tmp = dollarpars(line, tmp, all); // write this! to return ptr before delimiter
		}	
		else if (ft_strchr(delimiters, *tmp))
			tmp = tokencrtr(line, tmp, &genlist, &all); // to proceed the token and shift line pointer
		else
			tmp++;
		//if (*tmp == ';')
		//	executer(genlist);
		//else if (*tmp == '|')

	}
	tokencrtr(line, tmp, &genlist, &all);
	if ((pipecount = pipefinder(genlist)))
    	ft_pipe(&all, genlist, pipecount);
	//else if (genlist->set->direct)
	//{
	//	executer(genlist, dir_exec(pipe_init(), genlist->set->direct), &all);
	//}
	else
		executer(genlist, &all, 0);
}