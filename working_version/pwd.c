#include "minishell.h"

void ft_pwd(t_all *all)
{
   char dir[500];
   int	descr;
   
    getcwd(dir, 500);
    write(1, dir, ft_strlen(dir));
    dup2(1, descr);
    if (descr != 1)
    	close(descr);
    dup2(all->fd_1, 1);
    write(1, "\n", 1);
    errno = 0;
}
