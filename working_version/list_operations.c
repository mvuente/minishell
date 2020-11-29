#include "minishell.h"

t_list	*ft_create_item(char *data)
{
	t_list	*item;

	if (!(item = (t_list*)malloc(sizeof(t_list))))
		malloc_error();
	//printf("new t_list addres is %p\n", item);
	item->next = NULL;
	item->word = data;
	//printf("and data adress inside is %p\n", item->word);
	return (item);
}

t_list	*lstaddback(t_list *word, char *item)
{
	t_list	*tmp;

	//printf("item fro lstadd %s\n", item);
	if (!word)
		return (ft_create_item(item));
	tmp = word;
	while (tmp->next)
	{
	//	write(1, "P", 1);
		tmp = tmp->next;
	}
	tmp->next = ft_create_item(item);
	//tmp = word;
	//while (tmp)
	//{
	//	printf("item in list is %s\n", tmp->word);
	//	tmp = tmp->next;
	//}
	return (word);
}
