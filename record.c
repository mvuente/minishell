/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 01:05:06 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/30 01:05:09 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_set	builtinrcrdr(char *item, t_set set)
{
	if (!(set.builtin))
		set.builtin = item;
	else if (!set.word && !set.spec)
	{
		if (!ft_memcmp(item, "-n", 3))
		{
			set.spec = 0x1;
			free(item);
		}
		else
			set.word = lstaddback(set.word, item);
	}
	else
		set.word = lstaddback(set.word, item);
	return (set);
}
