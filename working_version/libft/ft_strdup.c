/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 10:32:17 by mvuente           #+#    #+#             */
/*   Updated: 2020/05/27 17:00:10 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *s)
{
	char	*res;
	size_t	i;

	i = ft_strlen(s);
	res = (char *)malloc(sizeof(char) * i + 1);
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, s, i);
	res[i] = '\0';
	return (res);
}
