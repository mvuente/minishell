/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvuente <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 10:36:09 by mvuente           #+#    #+#             */
/*   Updated: 2020/05/30 16:32:38 by mvuente          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nmbwrd(char const *s, char c)
{
	int	wrd;
	int	let;

	wrd = 0;
	let = 0;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (*s == c)
			let = 0;
		else if (let == 0)
		{
			let = 1;
			wrd++;
		}
		s++;
	}
	return (wrd);
}

static int		ft_wlength(char const *s, char c, int i)
{
	int	lenght;

	lenght = 0;
	while (s[i] != c && s[i] != '\0')
	{
		lenght++;
		i++;
	}
	return (lenght);
}

static char		**ft_free(char const **res, int j)
{
	while (j > 0)
	{
		j--;
		free((void *)res[j]);
	}
	free(res);
	return (NULL);
}

static char		**ft_maker(char const *s, char **res, char c, int nmbwords)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < nmbwords)
	{
		k = 0;
		while (s[i] == c)
			i++;
		res[j] = (char *)malloc(sizeof(char) * ft_wlength(s, c, i) + 1);
		if (res[j] == NULL)
			return (ft_free((char const **)res, j));
		while (s[i] != '\0' && s[i] != c)
			res[j][k++] = s[i++];
		res[j][k] = '\0';
		j++;
	}
	res[j] = 0;
	return (res);
}

char			**ft_split(char const *s, char c)
{
	char	**res;
	int		nmbwords;

	if (s == NULL)
		return (NULL);
	nmbwords = nmbwrd(s, c);
	res = (char **)malloc(sizeof(char *) * (nmbwords + 1));
	if (res == NULL)
		return (NULL);
	return (ft_maker(s, res, c, nmbwords));
}
