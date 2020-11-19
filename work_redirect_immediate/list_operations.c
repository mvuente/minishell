#include "minishell.h"

t_list	*ft_create_item(char *data)
{
	t_list	*item;

	if (!(item = (t_list*)malloc(sizeof(t_list))))
		malloc_error();
	item->next = NULL;
	item->word = data;
	return (item);
}

t_list	*lstaddback(t_list *word, char *item)
{
	t_list	*tmp;

	if (!word)
		return (ft_create_item(item));
	tmp = word;
	while (tmp) 
		tmp = tmp->next;
	tmp = ft_create_item(item);
	return (word);
}
