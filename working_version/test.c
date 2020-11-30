/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:17:45 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/30 11:17:47 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char *argv[], char *env[])
{
	t_env	*bufenv;
	t_all	all;

	ft_init_all(&all, env, bufenv);
	minishell(all);
	return (0);
}
