/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 10:31:59 by mvuente           #+#    #+#             */
/*   Updated: 2020/05/28 22:12:24 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*res;
	char	smb;

	smb = (char)c;
	res = (char *)s;
	while (*res)
	{
		if (*res == smb)
			return (res);
		res++;
	}
	if (*res == '\0' && smb == '\0')
		return (res);
	return (NULL);
}
