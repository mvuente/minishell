/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 16:48:40 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/29 16:55:50 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_work_tilda(t_all *all, char *path, char *home)
{
	char *tmp;

	tmp = path;
	if (path[1] != '/')
	{
		path = home;
		if (!path)
			path = all->home;
	}
	else
	{
		if (!home)
			path = ft_strjoin(all->home, path + 1);
		else
			path = ft_strjoin(home, path + 1);
	}
	return (path);
}

void	ft_write_cd(char *path, char *pwd)
{
	ft_putstr_fd("bash_na_bash: cd: ", 2);
	write(2, path, ft_strlen(path));
	ft_putendl_fd(": No such file or directory", 2);
	if (pwd)
		free(pwd);
}

int		ft_home_cd(char *pwd)
{
	ft_putendl_fd("bash_na_bash: cd: HOME not set", 2);
	if (pwd)
		free(pwd);
	return (126);
}

int		ft_cd(t_all *all, t_set *set)
{
	char	*home;
	char	*pwd;
	char	*path;

	pwd = getcwd(NULL, 0);
	home = ft_get_value(all->myenv, "HOME");
	if (set->word)
		path = set->word->word;
	else
	{
		path = home;
		if (!path)
			return (ft_home_cd(pwd));
	}
	if (path[0] == '~')
		path = ft_work_tilda(all, path, home);
	if ((chdir(path)) != 0)
	{
		ft_write_cd(path, pwd);
		return (1);
	}
	else
		ft_change_oldpwd(all->myenv, pwd, NULL, path);
	return (0);
}
