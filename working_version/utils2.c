#include "minishell.h"

void	ft_change_data(t_env *tmp, int flag, char *str)
{  
    flag = 1;
    free(tmp->data);
    tmp->data = NULL;
          
    if (!(tmp->data = ft_strdup((ft_strchr(str, '=') + 1))))
		malloc_error();
}

void	ft_free_set(t_set *set)
{
	t_list	*tmp;

	tmp = set->word;
	while(tmp)
	{
       free(tmp->word);
        tmp = tmp->next;
    }
   if (set->builtin)
        free(set->builtin);
    free(set->word);
    free(set);
}

void	cleargenlist(t_genlist *genlist)
{
	t_genlist	*templist;
	t_genlist	*tmp;

	templist = genlist;
	while (templist)
	{
		tmp = templist;
		ft_free_set(templist->set);
		templist = templist->next;
		free(tmp);
	}
	return ;
}

int		*pipe_init(void)
{
	int	fd[2];
	int	*tmp;

	fd[0] = 0;
	fd[1] = 1;
	//if (pipe(fd) < 0)
	//	some_error();
	//printf("I'm here!\n");
	tmp = fd;
	return (tmp);
}