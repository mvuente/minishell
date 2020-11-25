/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:30:38 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/25 10:00:56 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_oldpwd(t_env *myenv, char *pwd, char *tmp, char *path)
{
	while (myenv)
	{
		if (ft_strncmp(myenv->name, "PWD", 4) == 0 && myenv->data)
		{
			if (ft_strncmp(myenv->name, "PWD", 4) == 0 && myenv->data)
			{
				tmp = myenv->data;
				myenv->data = getcwd(NULL, 0);
				free(tmp);
			}
			myenv = myenv->next;
			tmp = myenv->data;
			myenv->data = getcwd(NULL, 0);
			free(tmp);
		}
		if (ft_strncmp(myenv->name, "OLDPWD", 7) == 0 && myenv->data)
		{
			tmp = myenv->data;
			myenv->data = ft_strdup(pwd);
			free(tmp);
			free(pwd);
		}
		myenv = myenv->next;
	}
}

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
	free(tmp);
	return (path);
}

void	ft_cd(t_all *all, t_set *set)
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
			path = all->home;
	}
	if (path[0] == '~')
		path = ft_work_tilda(all, path, home);
	if ((chdir(path)) != 0) //return 1 or 0
	{
		write(1, "cd: ", 4);
		write(1, path, ft_strlen(path));
		ft_putendl_fd(": No such file or directory", 1);
		return ;//(1);
	}
	else
		ft_change_oldpwd(all->myenv, pwd, NULL, path);
    //return (0);
}
