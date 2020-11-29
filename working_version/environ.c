/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 15:47:21 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/26 15:47:42 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_value(t_env *myenv, char *name)
{
	int		i;

	i = ft_strlen(name);
	while (myenv)
	{
		if (!ft_memcmp(myenv->name, name, i + 1) && \
		i == ft_strlen(myenv->name))
		{
			return (myenv->data);
		}
		myenv = myenv->next;
	}
	return (NULL);
}
