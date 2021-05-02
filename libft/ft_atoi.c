/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 10:27:33 by mvuente           #+#    #+#             */
/*   Updated: 2020/05/27 15:31:48 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *ptr)
{
	int res;
	int i;
	int flag;

	res = 0;
	i = 0;
	flag = 1;
	while (ptr[i] != '\0' && (ptr[i] == ' ' || ptr[i] == '\n' ||
		ptr[i] == '\v' || ptr[i] == '\t' || ptr[i] == '\r' ||
		ptr[i] == '\f'))
		i++;
	if (ptr[i] == '-')
		flag = -1;
	if (ptr[i] == '+' || ptr[i] == '-')
		i++;
	while (ptr[i] != '\0' && ptr[i] >= '0' && ptr[i] <= '9')
	{
		res = ptr[i] - '0' + res * 10;
		i++;
	}
	return (res * flag);
}
