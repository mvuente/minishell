#include "minishell.h"

int     *dir_exec(int *fd, t_dirlist *direct)
{
    t_dirlist	*tmp;

	tmp = direct;
	while (tmp)
	{
		if (fd[0] && *tmp->direct == 0x3c)
        	close(fd[0]);
		else if (fd[1] != 1 && *tmp->direct == 0x3e)
        	close(fd[1]);
    	if (*tmp->direct == 0x3c)
		{
			if ((fd[0] = open(tmp->fname, O_RDONLY)) == -1)
				{
					fd[0] = 0;
					write(1, "No such file or directory", 25); // нужен ошибка и minishell()
				}
		}
    	else if (!ft_memcmp(">", tmp->direct, 2))
    	{
    	//printf("operator detected\n");
			fd[1] = open(tmp->fname, O_RDWR | O_CREAT, S_IRWXU);
    	}
    	else
		{
        //printf("wrong operator detected\n");
			fd[1] = open(tmp->fname, O_RDWR | O_CREAT| O_APPEND, S_IRWXU);
		}
		tmp = tmp->next;
	}
    
   	//printf("opened descriptor is %i\n", *(*fd + 1));
	return (fd);
}

void	dir_exec_pipe(int *fd, t_dirlist *direct)
{
    t_dirlist	*tmp;
	//char		*test;

	//printf("I'm here?\n");
	tmp = direct;
	dup2(0, fd[0]);
	dup2(1, fd[1]);
	while (tmp)
	{
		if (fd[0] && *tmp->direct == 0x3c)
        	close(fd[0]);
		else if (fd[1] != 1 && *tmp->direct == 0x3e)
        	close(fd[1]);
    	if (*tmp->direct == 0x3c)
		{
			if ((fd[0] = open(tmp->fname, O_RDONLY)) == -1)
				{
					fd[0] = 0;
					write(1, "No such file or directory\n", 26); // нужен ошибка и minishell()
				}
			//printf("opened file is %i\n", fd[0]);
			//dup2(0, fd[0]);
			dup2(fd[0], 0);
			//printf("crazy %i\n", fd[0]);
			//read(0, test, 1);
			//printf("WTF? %s\n", test);
		}
    	else if (!ft_memcmp(">", tmp->direct, 2))
			fd[1] = open(tmp->fname, O_RDWR | O_CREAT, S_IRWXU);
    	else
			fd[1] = open(tmp->fname, O_RDWR | O_CREAT| O_APPEND, S_IRWXU);
		dup2(fd[1], 1);
		tmp = tmp->next;
		//printf("fd[0] is %i\n", fd[0]);
		//printf("fd[1] is %i\n", fd[1]);
	}
	return ;
}