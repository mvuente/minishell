/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:54:56 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/30 21:54:58 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_oldpwd(char *data, char *pwd, char *tmp)
{
	tmp = data;
	data = ft_strdup(pwd);
	free(tmp);
	free(pwd);
	errno = 222;
	return (data);
}

void	ft_add_oldpwd(char *pwd, t_env *myenv)
{
	char	*str;

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
			myenv->data = ft_oldpwd(myenv->data, pwd, tmp);
		myenv = myenv->next;
	}
	if (errno != 222)
		ft_add_oldpwd(pwd, tmpenv);
}
