/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 13:06:40 by mvuente           #+#    #+#             */
/*   Updated: 2020/10/22 13:06:42 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//t_genlist	*genlstcrtr(char *delim, t_genlist *genlist)
//{
//	t_genlist	*tmp;
//
//	if (!(tmp = (t_genlist*)malloc(sizeof(t_genlist))))
//		malloc_error();
//	tmp->next = NULL;
//	tmp->set = NULL;
//	genlist = tmp;
//	return ;
//}

t_env	*ft_lstnew_env(char *content)
{
	t_env	*newlist;
    int i;

    i = 0;
	if (!(newlist = (t_env*)malloc(sizeof(t_env))))
		malloc_error();
    if (ft_strchr(content, '='))
	{
		if (!(newlist->data = ft_strdup((ft_strchr(content, '=') + 1))))
			malloc_error();
	}
    else
        newlist->data = NULL;
    
    newlist->content = content;
    while (content[i] != '=' && content[i])
      i++;
    if (!(newlist->name = ft_calloc(sizeof(char), i + 1)))
		malloc_error();
    ft_strlcpy(newlist->name, content, i + 1);
   	newlist->next = NULL;
	return (newlist);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*buffer;

	if (!new)
		return ;
	if (*lst)
	{
		buffer = *lst;
		while (buffer->next)
		    buffer = buffer->next;
		buffer->next = new;
	}
	else
		*lst = new;
	return ;
}

void	genlstadd(char *delim, t_genlist **genlist)
{
	(*genlist)->set->consq = *delim;
	(*genlist)->next = initial_genlist();
	return ;
}

int	ft_lstsize_env(t_env *lst)
{
    int i;

	if (!lst)
		return (0);
	i = 1;
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

