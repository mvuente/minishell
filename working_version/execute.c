#include "minishell.h"

void	echo_executer(t_set *set, int **fd, t_all *all)
{
	int 	descr;
    t_list  *tmp;

    //printf("builtin is %s\n", set->builtin);
    //printf("word is %s\n", set->word);
    //printf("descrioptor is %i\n", *(*fd + 1));
    tmp = set->word;
	if (tmp)
	{
		write(*(*fd + 1), tmp->word, ft_strlen(tmp->word));
		tmp = tmp->next;
	}
	while (tmp)
	{
		write(*(*fd + 1), " ", 1);
		write(*(*fd + 1), tmp->word, ft_strlen(tmp->word));
		tmp = tmp->next;  // echo 123>file    TO DO!!!
	}
    if (!set->spec)
        write(*(*fd + 1), "\n", 1);
    if (*(*fd + 1) != 1)
        close(*(*fd + 1));
    *(*fd + 1) = 1;
    write(1, "\n", 1);
    //minishell(*all);
}

void    executer(t_genlist *genlist, int **fd, t_all *all)
{
    t_genlist   *tmp;

    tmp = genlist;
    if (!tmp->set->builtin)
    	write(1, "\n", 1);
    else if (!ft_memcmp(tmp->set->builtin, "pwd", 4))
        ft_pwd(fd, all);
    else if (!ft_memcmp(tmp->set->builtin, "echo", 5))
        echo_executer(tmp->set, fd, all);
    else if (!ft_memcmp(tmp->set->builtin, "export", 7))
        export_executer(tmp->set, fd, all);
	else if (!ft_memcmp(tmp->set->builtin, "cd", 3))
        ft_cd(all, tmp->set->word->word);
    else if (!ft_memcmp(tmp->set->builtin, "env", 4))
        env_executer(tmp->set, fd, all);
    else if (!ft_memcmp(tmp->set->builtin, "unset", 6))
        unset_executer(tmp->set, fd, all);
	else if (!ft_memcmp(tmp->set->builtin, "exit", 5))
		ft_exit(all, tmp->set, fd);
    else
    {
        write(1, "e-bash!: wrong command! try again.", 34);
        write(1, "\n", 1);
        //minishell(*all);
    }
    return ;
}