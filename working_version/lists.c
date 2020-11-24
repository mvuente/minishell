#include "minishell.h"

//t_list	*listcrtr(t_set set)
//{
//	t_list	*list;
//
//	if (!(list = (list*)malloc(sizeof)list))
//		malloc_error();
//	list->set = set;
//	list->next = NULL;
//	return (list);
//}

//t_list	*listadd(t_list *list, t_set set)
//{
//	t_list	*newitem;
//	t_list	*tmp;
//
//	newitem = listcrtr(set);
//	tmp = list;
//	while (tmp)
//		tmp = tmp->next;
//	tmp = newitem;
//	return (list);
//}

//t_list	*listoper(t_set set, t_list *list)
//{
//	if (!list)
//		return (listcrtr(set));
//	return (listadd(list, set));
//}

t_dirlist	*dirlistcrtr(char *direction, char *fname)
{
	t_dirlist	*direct;

	if (!(direct = (t_dirlist*)malloc(sizeof(t_dirlist))))
		malloc_error();
	direct->direct = direction;
	direct->fname = fname;
	direct->next = NULL;
	return (direct);
}