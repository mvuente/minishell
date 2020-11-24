#include "minishell.h"

void ft_pwd(int *fd, t_all *all)
{
   char dir[500];
   
    getcwd(dir, 500);
    write(fd[1], dir, ft_strlen(dir));
    if (fd[1] != 1)
    {
        write(fd[1], "\n", 1);
        close(fd[1]);
        fd[1] = 1;
    }
    write(1, "\n", 1);
	//minishell(*all);   
}
