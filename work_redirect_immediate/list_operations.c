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

//t_list	*ft_create_item(char *data)
//{
//	t_list	*item;
//
//	if (!(item = (t_list*)malloc(sizeof(t_list))))
//		malloc_error();
//	item->next = NULL;
//	item->direct->sign = data;
//	return (item);
//}

//t_list	*lstaddfront(t_list *word, char *item)
//{
//	t_list	*tmp;
//
//	if (!word)
//		return (ft_create_item(item));
//	tmp = ft_create_item(item);
//	tmp->next = word;
//	return (tmp);
//}

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

void	genlstadd(char *delim, t_genlist **genlist)
{
	(*genlist)->set->consq = *delim;
	(*genlist)->next = initial_genlist();
	return ;
}

