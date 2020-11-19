/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 13:18:41 by mvuente           #+#    #+#             */
/*   Updated: 2020/05/27 15:33:28 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;
	int				i;

	i = 0;
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (n--)
	{
		if (*(a + i) != *(b + i))
			return (*(a + i) - *(b + i));
		i++;
	}
	return (0);
}
