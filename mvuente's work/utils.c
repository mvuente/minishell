#include "minishell.h"



t_set	*initial_set(void)
{
	t_set	*set;

	if (!(set = (t_set*)malloc(sizeof(t_set))))
		malloc_error();
	set->builtin = NULL;
	set->divider = NULL;
	set->word = NULL;
	set->spec = NULL;
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

char	*low(char *item)
{
	char	*str;
	
	str = item;
	while (*str)
	{
		*str = ft_tolower(*str);
		str++;
	}
	return (item);
}

char	*itemcrtr(char **line, char *tmp)
{
	char	*item;

	if (!(item = ft_calloc(tmp - *line + 1, sizeof(char))))
		malloc_error;
	item = ft_memmove(item, *line, tmp - *line);
	*line = tmp + 1;
	return (item);
}