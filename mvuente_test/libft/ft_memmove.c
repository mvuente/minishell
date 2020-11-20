/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 10:31:24 by mvuente           #+#    #+#             */
/*   Updated: 2020/05/30 16:38:37 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*frst;
	unsigned char	*scnd;
	size_t			i;

	frst = (unsigned char *)src;
	scnd = (unsigned char *)dest;
	i = 0;
	if (frst < scnd)
	{
		while (n--)
			scnd[i + n] = frst[i + n];
	}
	else
	{
		while (i < n)
		{
			scnd[i] = frst[i];
			i++;
		}
	}
	return (scnd);
}
