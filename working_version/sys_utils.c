/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:37:51 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/30 16:37:53 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_creat_arr_comanda(char *comanda, t_set *set, char *str)
{
	char	*tmp;
	char	**arr;
	int		i;

	i = ft_strlen(comanda);
	if (str)
	{
		tmp = ft_strjoin_export(comanda, "!", str);
		arr = ft_split(tmp, '!');
		free(tmp);
	}
	else
		arr = ft_split(comanda, ' ');
	g_flag = 1;
	return (arr);
}

char	*ft_for_syscall(char *path, int fd, int flag)
{
	char	*comanda;

	close(fd);
	comanda = ft_strdup(path);
	return (comanda);
}

char	*ft_check_syscall(t_env *bufenv, t_set *set, int fd, int flag)
{
	char	*path;
	int		a;
	char	*comanda;
	char	**arr;

	comanda = NULL;
	path = ft_get_value(bufenv, "PATH");
	if (!path && ft_strncmp(set->builtin, "/", 1))
		comanda = ft_strdup("PATH=NULL");
	else if (set->builtin[0] == '/' && ft_strchr(set->builtin + 1, '/'))
		comanda = ft_strdup(set->builtin);
	else
	{
		arr = ft_split(path, ':');
		a = -1;
		while (arr[++a] && !ft_strchr(set->builtin, '/'))
		{
			path = ft_strjoin_export(arr[a], "/", set->builtin);
			if ((fd = open(path, O_RDONLY)) > 0 && flag == 0)
				comanda = ft_for_syscall(path, fd, ++flag);
			free(path);
		}
		ft_free_arr(arr);
	}
	return (comanda);
}
