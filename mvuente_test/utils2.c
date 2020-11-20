#include "minishell.h"

void	ft_change_data(t_env *tmp, int flag, char *str)
{  
    flag = 1;
    free(tmp->data);
    tmp->data = NULL;
          
    if (!(tmp->data = ft_strdup((ft_strchr(str, '=') + 1))))
		malloc_error();
}
