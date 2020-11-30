/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:57:35 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/26 15:39:13 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_str(t_list *word)
{
	char	*str;
	t_list	*tmp;
	char	*tmpstr;

	str = NULL;
	tmp = word;
	if (tmp->word)
	{
		str = ft_strdup(word->word);
		tmp = tmp->next;
	}
	while (tmp)
	{
		tmpstr = str;
		str = ft_strjoin_export(str, "!", tmp->word);
		tmp = tmp->next;
		free(tmpstr);
	}
	return (str);
}

void	ft_free_syscall(char *comanda, char **env, char *str, char **arr)
{
	if (str)
		free(str);
	if (comanda)
		free(comanda);
	ft_free_arr(env);
	if (arr)
		ft_free_arr(arr);
}

void	ft_write_syscall(char *builtin)
{
	ft_putstr_fd("bash_na_bash:", 2);
	ft_putstr_fd(builtin, 2);
	ft_putstr_fd(": command not found\n", 2);
}

int		ft_execve(char *comanda, char **arr, char **env, char *builtin)
{
	int i;

	if (!comanda)
		comanda = builtin;
	if ((i = execve(comanda, arr, env)) < 0)
		i = 127;
	if (!ft_strchr(builtin, '/') && ft_strncmp(comanda, "PATH=NULL", 10) != 0)
		ft_write_syscall(builtin);
	else if (errno == 2 || (errno == 14 && !comanda))
	{
		ft_putstr_fd("bash_na_bash:", 2);
		ft_putstr_fd(builtin, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		ft_putstr_fd("bash_na_bash:", 2);
		ft_putstr_fd(builtin, 2);
		ft_putstr_fd(":is a directory\n", 2);
		i = 126;
	}
	return (i);
}

int		ft_syscall(t_all *all, t_set *set, t_env *bufenv)
{
	char	*comanda;
	char	**env;
	char	**arr;
	char	*str;

	str = NULL;
	arr = NULL;
	comanda = NULL;
	if (set->word)
		str = ft_add_str(set->word);
	env = ft_creat_arr_export(bufenv, ft_lstsize_env(bufenv));
	if (!(comanda = ft_check_syscall(bufenv, set, 0, 0)) || comanda[0] != '/')
		arr = NULL;
	else
		arr = ft_creat_arr_comanda(comanda, set, str);
	if ((all->pid = fork()) == -1)
		return (1);
	if (all->pid == 0)
		exit(ft_execve(comanda, arr, env, set->builtin));
	else
		waitpid(all->pid, &all->status, 0);
	all->error = WEXITSTATUS(all->status);
	g_flag = 0;
	ft_free_syscall(comanda, env, str, arr);
	return (all->error);
}
