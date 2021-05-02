/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 10:35:38 by mvuente           #+#    #+#             */
/*   Updated: 2020/05/28 21:58:32 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *c, int fd)
{
	size_t length;

	length = ft_strlen(c);
	if (c == NULL || fd < 0)
		return ;
	write(fd, c, length);
	write(fd, "\n", 1);
}
