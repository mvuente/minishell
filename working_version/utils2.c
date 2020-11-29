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
	t_list		*tmp;
	t_list		*todie;
	t_dirlist	*dirtmp;
	t_dirlist	*dirtodie;

	tmp = set->word;
	while(tmp)
	{
    	todie = tmp;
		//printf("i try to free addres %p\n", tmp->word);
		free(tmp->word);
		free(todie);
        tmp = tmp->next;
    }
	dirtmp = set->direct;
	while(dirtmp)
	{
    	dirtodie = dirtmp;
		free(dirtmp->direct);
		free(dirtmp->fname);
    	dirtmp = dirtmp->next;
		free(dirtodie);
    }
	//if (set->direct)
	//	free(set->direct);
	if (set->builtin)
        free(set->builtin);
    //if (set->word)
	//	free(set->word);
    free(set);
	return ;
}

void	cleargenlist(t_genlist *genlist)
{
	//t_genlist	*templist;
	//t_genlist	*tmp;

	//templist = genlist;
	//while (templist)
	//{
	//	tmp = templist;
	//	ft_free_set(templist->set);
	//	templist = templist->next;
	//	free(tmp);
	//}
	free(genlist);
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

//t_genlist	*rotor(int	size, t_genlist *genlist)
//{
//	t_genlist	*tmp;
//
//	tmp = genlist;
//	while (size > 0)
//	{
//
//	}
//}