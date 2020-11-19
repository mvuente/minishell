   #include "minishell.h"

void ft_add_env(char *str, t_env *bufenv)
{
   t_env *tmp;
   int flag;
   int i;
   char *name;
   int a = 0;
   
   flag = 0;
   tmp = bufenv;
   i = 0;
   while (str[i] != '=' && str[i])
    i++;
   name = ft_calloc(sizeof(char), i + 1);
   ft_strlcpy(name, str, i + 1);
   while (tmp && flag == 0)
   {
        if (ft_strncmp(tmp->name, name, i) == 0 && i == ft_strlen(tmp->name))// && tmp->data)
          {
            flag++;
            if (ft_strchr(str, '='))
                ft_change_data(tmp, flag, str);
          }
        tmp = tmp->next;
   }
   if (flag == 0)
        ft_lstadd_back_env(&bufenv, ft_lstnew_env(str)); //если уже есть новую не создает
}

void	ft_write_export(t_env *bufenv, int fd, int num)
{
    int i;
    int j;
    char **arr;

    arr = ft_creat_arr_export(bufenv, num);
	ft_sort(bufenv, arr, num-1);
	i = -1;
    while(arr[++i])
    {
        j = 0;
        while (arr[i][j] && arr[i][j] != '=')
            j++;
        ft_putstr_fd("declare -x ", fd);
        write(fd, arr[i], j);
        if (ft_strchr(arr[i], '='))
        {
            ft_putstr_fd("=\"", fd);
            ft_putstr_fd(ft_strchr(arr[i], '=') + 1, fd);
            ft_putchar_fd('\"', fd);
        }
        ft_putchar_fd('\n', fd);
    }
    ft_free_arr(arr);
}

void	export_executer(t_set *set, int **fd, t_all *all)
{
	if (!set->word)
		ft_write_export(all->myenv, *fd[1], ft_lstsize_env(all->myenv));
	else
		ft_add_env(set->word, all->myenv);
}
