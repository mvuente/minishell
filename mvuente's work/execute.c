#include "minishell.h"

void    executer(t_genlist *genlist)
{
    t_genlist   *tmp;

    tmp = genlist;
    if (!ft_memcmp(tmp->set->builtin, "pwd", 3))
        ft_pwd();
    else
    {
        write(1, "e-bash!: wrong command! try again.", 34);
        write(1, "\n", 1);
        minishell();
    }
    return ;
    
}