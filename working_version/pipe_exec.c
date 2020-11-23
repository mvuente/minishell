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
       // printf("%d\n", size);
        size--;
    }

    return (pipefd);
}



int ft_work_pipe(t_all *all, t_genlist *pipes, int size, int **pipefd, int **fd)
{
    pid_t cpid;
    int status;
    int flag;

    flag = 0;     
     if ((cpid = fork())== -1)
        return(1);
        
        if (cpid == 0) 
        { // Потомок читает из канала 0 
           close(pipefd[size][0]); 
           //if (flag == 0)
            dup2(pipefd[size][1], 1); 
           //else 
             //  dup2(pipefd[size][1], pipefd[size+1][1]); 
            flag = 1;
           
           ft_exe_function(pipes, all, fd); // ту вызывается функция которая вызовет или системную или самописную
        } 
        else 
        {   
            close(pipefd[size][1]);         
            dup2(pipefd[size][0], 0);
            waitpid(cpid, &status, WUNTRACED);
           //printf("%d\n", size);
           if (size < 1) // значит что это последня команда и надо вернуть fd в первоначально состояние, чтобы ушло в стдаут терминал
              {
                    dup2(all->fd_1, 1);
            }
           // else 
             //  dup2(pipefd[size-1][1], pipefd[size][0]);
            pipes = pipes->next;
            if (size < 1)
               {
                    ft_exe_function(pipes, all, fd);
                     dup2(all->fd_0, 0);
               } 
        }
    return (0);
}
// ft_pipe(&all, pipes, (ft_lstsize_pipes(pipes)) - 1);

int ft_pipe(t_all *all, t_genlist *pipes, int size, int **fd)
{
    int **pipefd;
    pid_t cpid;
    int flag;
    int status;
     
    if (!(pipefd = ft_init_pipefd(--size)))
        return (1);
    while (size >= 0)
    {
            printf("size = %d\n", size);
            ft_work_pipe(all, pipes, size, pipefd, fd);
        
        size--;
        pipes = pipes->next;
    }
   return (0);
}