#include "minishell.h"

void	echo_executer(t_set *set, int **fd)
{
	int descr;

    printf("builtin is %s\n", set->builtin);
    printf("word is %s\n", set->word);
    //if (*fd[1])
      //  descr = 1;
    //else
      //  descr = *fd[1];
    printf("descrioptor is %i\n", *(*fd + 1));
    write(*(*fd + 1), set->word, ft_strlen(set->word));
    if (!set->spec)
        write(*(*fd + 1), "\n", 1);
    if (*(*fd + 1) != 1)
        close(*(*fd + 1));
    *(*fd + 1) = 1;
}

void    executer(t_genlist *genlist, int **fd)
{
    t_genlist   *tmp;

    tmp = genlist;
    if (!ft_memcmp(tmp->set->builtin, "pwd", 3))
        ft_pwd();
    else if (!ft_memcmp(tmp->set->builtin, "echo", 4))
        echo_executer(tmp->set, fd);
    else
    {
        write(1, "e-bash!: wrong command! try again.", 34);
        write(1, "\n", 1);
        minishell();
    }
    return ;
    
}