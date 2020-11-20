#include "minishell.h"

void ft_write_exit(char *builtin, char **arr, int fd)
{
            ft_putstr_fd("bash: exit: ", fd);
            ft_putstr_fd(builtin, fd);
            ft_putstr_fd(": numeric argument required", fd);//выходит
            ft_free_arr(arr);
            exit(255);

}

int ft_exit(t_all *all, t_set *set, int fd)
{
   char **arr;
    int i;

    if (ft_strchr(set->builtin, '|'))
        return (0);
    arr = ft_split(set->builtin, ' ');
    i = -1;
    while(arr[0][++i])
    {
       if (!ft_isdigit(arr[0][i]))
            ft_write_exit(set->builtin, arr, fd);//выходит
    }
   if (arr[1])
    {
        ft_putendl_fd("bash: exit: too many arguments", fd);// не выходит
        all->error = 1;
        ft_free_arr(arr);
    }
    if (set->builtin)
        all->error = ft_atoi(set->builtin);
    exit(all->error);
}