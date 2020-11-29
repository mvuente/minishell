#include "minishell.h"

void ft_pwd(t_all *all)
{
   char dir[500];
   int	descr;
   getcwd(dir, 500);
   ft_putendl_fd(dir, 1);
   dup2(1, descr);
   close(descr);
   dup2(all->fd_1, 1);
   errno = 0;
}
