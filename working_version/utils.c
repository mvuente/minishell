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

char	*itemcrtr(char **line, char *tmp, int dolflag, t_all all)
{
	char	*item;
	char	*dollar;
	char	*ptr;

	if (!(item = ft_calloc(tmp - *line + 1, sizeof(char))))
		malloc_error();
	item = ft_memmove(item, *line, tmp - *line);
	//printf("item before creating is %c\n", *item);
	ptr = item;
	if (ft_strchr(item, 0x22) || ft_strchr(item, 0x27))
	{
		dolflag = 1;
		//ptr = item - 1;
	}
	*line = tmp;
	//printf("item before cqprocessor is %s\n", item);
	item = cqprocessor(ptr, dolflag, all); // it checks obtained item for quotes and (if yes), remotes them
	//printf("and result item is %s\n", item);
	return (item);
}