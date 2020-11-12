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

void	reader(char *line) //par of this func could be a parser function
{
    char		*tmp;
	char		*delimiters;
	char		*quot;
	//t_set		set;
	t_genlist	*genlist;

	delimiters = ";|<> ";
	quot = "\"\'";
	genlist = initial_genlist();
	tmp = line;
	//printf("parser started\n");
	while (*tmp != 0x0)// tokenazing starts
	{ 
		//printf("in 1-st loop\n");
		if (ft_strchr(quot, *tmp))
			tmp = cqpars(tmp, *tmp);
		else if (ft_strchr(delimiters, *tmp))
			tmp = tokencrtr(&line, tmp, &genlist); // to proceed the token and shift line pointer
		else
			tmp++;
		//if (*tmp == ';')
		//	executer(genlist);
		//else if (*tmp == '|')

	}
	tokencrtr(&line, tmp, &genlist);
	executer(genlist);
	
}