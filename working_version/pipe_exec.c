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



int ft_work_pipe(t_all *all, t_genlist *pipes, int size, int pipefd[2], int **fd)
{
    pid_t cpid;
    int status;
    int flag;
   
    flag = 0;     
     if ((cpid = fork())== -1)
        return(1);
        //ft_putendl_fd("hello", 1);
        if (cpid == 0) 
        { // Потомок читает из канала 0 
           close(pipefd[0]); 
           //if (flag == 0)
            dup2(pipefd[1], 1); 
           //else 
             //  dup2(pipefd[size][1], pipefd[size+1][1]); 
            flag = 1;
           ft_exe_function(pipes, all, fd);
           exit(0); /// тут надо вернуть status после системной команды
            
           } 
        else 
        {   
           close(pipefd[1]);         
           dup2(pipefd[0], 0); 

              waitpid(cpid, &status, WUNTRACED); //WNOHANG   WUNTRACED
          
          
           if (size < 1) // значит что это последня команда и надо вернуть fd в первоначально состояние, чтобы ушло в стдаут терминал
           {
                    dup2(all->fd_1, 1);
                   
           }
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
    int pipefd[2];
    pid_t cpid;
    int flag;
    int status;
     
    size--;
    while (size >= 0)
    {
            if (pipe(pipefd) == -1)
                retutn (0);
            //printf("built  %s\n", pipes->set->builtin);
            ft_work_pipe(all, pipes, size, pipefd, fd);
         
        size--;
        pipes = pipes->next;
        //printf("built  %s\n", pipes->set->builtin);
    }
   return (0);
}