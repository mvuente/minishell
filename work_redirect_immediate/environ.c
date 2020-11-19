#include "minishell.h"

char *ft_get_value(t_env *myenv, char *name)
{
    while (myenv)
        {
            if (!ft_memcmp(myenv->name, name, ft_strlen(myenv->name + 1)))
                return (myenv->data);
            myenv = myenv->next;
        }
    return(NULL);
}