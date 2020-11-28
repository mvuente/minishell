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

char *ft_oldpwd(char *data, char *pwd, char *tmp)
{

	tmp = data;
	data = ft_strdup(pwd);
	free(tmp);
	free(pwd);
	errno = 222;
	
	return(data);
}

void	ft_add_oldpwd(char *pwd, t_env *myenv)
{
	char *str;

	str = ft_strjoin_export("OLDPWD", "=", pwd);
	ft_lstadd_back_env(&myenv, ft_lstnew_env(str)); 
	free(str);
	free(pwd);

}

void	ft_change_oldpwd(t_env *myenv, char *pwd, char *tmp, char *path)
{
	t_env *tmpenv;
	
	tmpenv = myenv;
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
			myenv->data = ft_oldpwd(myenv->data, pwd, tmp);

		
		}
		myenv = myenv->next;
	}
	if (errno != 222)
		ft_add_oldpwd(pwd, tmpenv);
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

int	ft_cd(t_all *all, t_set *set)
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
		write(2, "cd: ", 4);
		write(2, path, ft_strlen(path));
		ft_putendl_fd(": No such file or directory", 2);
		return (1);//(1);
	}
	else
		ft_change_oldpwd(all->myenv, pwd, NULL, path);
    return (0);
}
