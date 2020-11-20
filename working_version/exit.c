#include "minishell.h"

void ft_write_exit(char *builtin, char **arr, int fd)
{
            ft_putstr_fd("bash: exit: ", fd);
            ft_putstr_fd(builtin, fd);
            ft_putstr_fd(": numeric argument required", fd);//выходит
            ft_free_arr(arr);
            exit(255);
}

void	ft_exit(t_all *all, t_set *set, int **fd) // НУЖЕН ЛИ FD???
{
	char **arr;
	int i;

    if (ft_strchr(set->consq, '|'))
    	//return (0);
		return ;
    arr = ft_split(set->builtin, ' '); //СТРОКИ 20, 25 И 33 МОЖЕТ НЕ НУЖНЫ... АРГУМЕНТЫ ЛЕЖАТ В СПИСКЕ SET->WORD
    i = -1;
    while(arr[0][++i])
    {
    	if (!ft_isdigit(arr[0][i]))
        	ft_write_exit(set->builtin, arr, 1);//ПРИ НЕОБХОДИМОСТИ ЗАМЕНИТЬ 1 НА АКТУАЛЬНЫЙ FD
    }
   if (arr[1])
    {
        ft_putendl_fd("bash: exit: too many arguments", 1);// не выходит ПРИ НЕОБХОДИМОСТИ ЗАМЕНИТЬ 1 НА АКТУАЛЬНЫЙ FD
        all->error = 1;
        ft_free_arr(arr);
    }
    if (set->builtin)
        all->error = ft_atoi(set->builtin);
    exit(all->error);
}