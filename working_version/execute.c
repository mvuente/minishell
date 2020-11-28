#include "minishell.h"

void    ft_exe_function(t_genlist *pipes, t_all *all, int *fd)
{
   // printf("\n%s\n", pipes->set->builtin);
     //printf("%d\n", fd);
    ft_syscall(all, pipes->set, all->myenv);
   
    
    //здесь надо сделать парсинг для обработки строк с командами
    // после обработки сделать условие для вызова системных или самописных файлов
}

void	echo_executer(t_set *set, t_all *all)
{
	int 	descr;
    t_list  *tmp;
    //int     tmpfd;

    //printf("builtin is %s\n", set->builtin);
    //printf("word is %s\n", set->word);
    //printf("descrioptor is %i\n", *(*fd + 1));
    tmp = set->word;
	//printf("word is %s\n", tmp->word);
    if (tmp)
	{
		write(1, tmp->word, ft_strlen(tmp->word));
		tmp = tmp->next;
	}
	while (tmp)
	{
		write(1, " ", 1);
		write(1, tmp->word, ft_strlen(tmp->word));
		tmp = tmp->next;  // echo 123>file    TO DO!!!
	}
    if (!set->spec)
        write(1, "\n", 1);
    //if (fd[1] != 1)
      //  close(fd[1]);
    //fd[1] = 1;
    dup2(1, descr);
    if (descr != 1)
    	close(descr);
    dup2(all->fd_1, 1);
    write(1, "\n", 1);
    errno = 0;
    //minishell(*all);
}

void    executer(t_genlist *genlist, t_all *all, int pipe_flag)
{
    t_genlist   *tmp;

    tmp = genlist;
    //printf("current command is %s\n", tmp->set->builtin);
    //printf("current argument is %s\n", tmp->set->word->word);
	if (tmp->set->direct)
		dir_exec(pipe_init(), tmp->set->direct);
    if (!tmp->set->builtin)
    	write(1, "\n", 1);
    else if (!ft_memcmp(tmp->set->builtin, "pwd", 4))
    	ft_pwd(all);
    else if (!ft_memcmp(tmp->set->builtin, "echo", 5))
    	echo_executer(tmp->set, all);
    else if (!ft_memcmp(tmp->set->builtin, "export", 7))
    	errno = export_executer(tmp->set, all);
	else if (!ft_memcmp(tmp->set->builtin, "cd", 3))
    	errno = ft_cd(all, tmp->set);
    else if (!ft_memcmp(tmp->set->builtin, "env", 4))
		errno = env_executer(tmp->set, all);
    else if (!ft_memcmp(tmp->set->builtin, "unset", 6))
    	errno = unset_executer(tmp->set, all);
	else if (!ft_memcmp(tmp->set->builtin, "exit", 5))
		errno = ft_exit(all, tmp->set);
    else
		errno = ft_syscall(all, tmp->set, all->myenv);
	if (!pipe_flag)
		dup2(all->fd_0, 0);
	dup2(all->fd_1, 1);
    return ;
}