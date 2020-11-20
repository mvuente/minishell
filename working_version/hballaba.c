#include "minishell.h"

char	*ft_strjoin_export(char const *s1, char const *s2, char const *s3)
{
	char	*str;
	size_t	lens1;
	size_t	lens2;
    size_t	lens3;

	lens1 = ft_strlen((char*)s1);
	lens2 = ft_strlen((char*)s2);
    lens3 = ft_strlen((char*)s3);
	if (!(str = (char*)malloc(lens1 + lens2 + lens3 + 1)))
		malloc_error();
	ft_strlcpy(str, s1, lens1 + 1);
	ft_strlcat(str, s2, lens2 + lens1 + 1);
    ft_strlcat(str, s3, lens3 + lens2 + lens1 + 1);
	return (str);
}

void    ft_creat_env(char *env[], t_env	**bufenv)
{
   int t = -1;

    while (env[++t])
        ft_lstadd_back_env(bufenv, ft_lstnew_env(env[t]));
	return ;
}


void	ft_init_all(t_all *all, char **env, t_env *bufenv)
{
    
    all->fd_0 = dup(0);
    all->fd_1 = dup(1);
    ft_creat_env(env, &bufenv);
    all->myenv = bufenv;
	return ;
}

void	ft_sort(t_env *bufenv, char **arr, int num)
{
    int i;
    int j;
    char *tmp;
   
    i = -1;
    while (num > ++i)
    {
        j = -1;
        while (++j < num - i)
        {
            if (ft_strncmp(arr[j], arr[j+1], 300) > 0)
            {
            	tmp = arr[j];
            	arr[j] = arr[j + 1];
            	arr[j + 1] = tmp;
            }
        }
    }
}

char	**ft_creat_arr_export(t_env *bufenv, int size) // скорее всего здесь утечка
{
   char **arr;
   int i;
   char *content;

   i = 0;
   if (!(arr = (char**)malloc(sizeof(char*) * (size + 1))))
        malloc_error();
   while (bufenv)
	{
		if (bufenv->data)
            content = ft_strjoin_export(bufenv->name, "=", bufenv->data);
        else 
            content = bufenv->name;
        if (!(arr[i] = (char*)malloc(sizeof(char) * (ft_strlen(content) + 1))))
			malloc_error();
		ft_memcpy(arr[i], content, ft_strlen(content) + 1);
		bufenv = bufenv->next;
		i++;
        free(content);
	}
	arr[i] = NULL;
    return (arr);
}

