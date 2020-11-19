#include "minishell.h"

void ft_pwd(t_all *all)
{
   char dir[500];
   
    getcwd(dir, 500);
    printf("Current directory is %s\n", dir);
    write(1, "\n", 1);
    minishell(*all);   
}
