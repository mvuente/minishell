#include "minishell.h"

int ft_lstsize_pipes(t_genlist *lst)
{
    int i;

	if (!lst)
		return (0);
	i = 1;
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int **ft_init_pipefd(int size)
{
    int **pipefd;
	
	if (!(pipefd = (int**)malloc(sizeof(int*) * size + 1)))
		malloc_error();
    while (size >= 0)
    {
        if (!(pipefd[size] = (int*)malloc(sizeof(int) * 2)))
			malloc_error();
        if (pipe(pipefd[size]) == -1)
            return (0);
        size--;
    }
    return (pipefd);
}

int ft_work_pipe(t_all *all, t_genlist *pipes, int size, int pipefd[2])
{
    pid_t cpid;
    int status;
   // int flag;
   
    //flag = 0;     
     if ((cpid = fork())== -1)
        return(1);
        if (cpid == 0) 
        {
           close(pipefd[0]); 
            dup2(pipefd[1], 1); 
           // flag = 1;
			if (pipes->set->direct)
				dir_exec(pipe_init(), pipes->set->direct);
            executer(pipes, all, 1);
            close(pipefd[1]); 
            exit(0);
        } 
        else 
        {   
           close(pipefd[1]); 
           dup2(pipefd[0], 0); 
           waitpid(cpid, &status, WUNTRACED);
           pipes = pipes->next;
           if (size < 1)
              executer(pipes, all, 0);
            close(pipefd[0]); 
        }
    return (0);
}

int ft_pipe(t_all *all, t_genlist *pipes, int size)
{
    int 		pipefd[2];
    pid_t 		cpid;
    //int 		flag;
    int 		status;
	
	size--;
    while (size >= 0)
    {
        if (pipe(pipefd) == -1)
                return (0);
        ft_work_pipe(all, pipes, size, pipefd);
          size--;
	    pipes = pipes->next;
    }
   return (0);
}