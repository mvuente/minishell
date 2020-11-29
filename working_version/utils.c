#include "minishell.h"

void    ft_free_arr(char **arr)
{
    int i;

    i = -1;
    while (arr[++i])
       free(arr[i]);
    free(arr);   
}

t_set	*initial_set(void)
{
	t_set	*set;

	if (!(set = (t_set*)malloc(sizeof(t_set))))
		malloc_error();
	set->builtin = NULL;
	set->word = NULL;
	set->direct = NULL;
	set->spec = 0x0;
	set->consq = 0x0;
	set->fd[0] = 0;
	set->fd[1] = 0;
	return (set);
}

t_genlist	*initial_genlist(void)
{
	t_genlist	*genlist;

	if (!(genlist = (t_genlist*)malloc(sizeof(t_genlist))))
		malloc_error();
	genlist->set = initial_set();
	genlist->next = NULL;
	return (genlist);
}

//char	*low(char *item)
//{
//	char	*str;
//	
//	str = item;
//	while (*str)
//	{
//		*str = ft_tolower(*str);
//		str++;
//	}
//	return (item);
//}

char	*itemcrtr(char **line, char *finish, int dolflag, t_all all)
{
	char	*item;
	char	*dollar;
	char	*cqptr;
	char	*tmp;
	char	*quotset;

	quotset = "\"\'";
	if (!(item = ft_calloc(finish - *line + 1, sizeof(char))))
		malloc_error();
	item = ft_memmove(item, *line, finish - *line);
	//printf("item before creating is %c\n", *item);
	cqptr = item;

	while (*cqptr != 0x0)
	{
		//if ((tmp = ft_strchr(cqptr, 0x22)))
		//	cqptr = tmp;
		//else if ((tmp = ft_strchr(cqptr, 0x27)))
		//	cqptr = tmp;
		if (ft_strchr(quotset, *cqptr))
		{
			//printf("BEFORE cqprocessor CQPTR is %s\n", cqptr);
			dolflag = 1;
			item = cqprocessor(item, &cqptr, dolflag, all); // it checks obtained item for quotes and (if yes), remotes them
		//	printf("and AFTER cqproc CQPTR is %s\n", cqptr);
		}
		else
		{
			cqptr++;
			//*line = finish;
			//return (item);
		}
		
		//ptr = item - 1;
	}
	//free(*line);
	*line = finish;
	//printf("i've got an item and it's adress is %p\n", item);
	return (item);
}