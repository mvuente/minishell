#include "minishell.h"

void ft_write_exit(char *word, int fd)
{
            ft_putstr_fd("e_bash: exit: ", fd);
            ft_putstr_fd(word, fd);
            ft_putendl_fd(": numeric argument required", fd);//выходит
            exit(255);
}

void	ft_exit(t_all *all, t_set *set, int **fd) // НУЖЕН ЛИ FD???
{
	//char **arr;
	int i;
   // ft_putendl_fd(set->word->word, 1);
   if (!set->word)
        exit(0);
    if (ft_strchr(&set->consq, '|')) //// подумать куда пайп положить и что с ним
    	//return (0);
		return ;
    //arr = ft_split(set->builtin, ' '); //СТРОКИ 20, 25 И 33 МОЖЕТ НЕ НУЖНЫ... АРГУМЕНТЫ ЛЕЖАТ В СПИСКЕ SET->WORD
    i = -1;
    while(set->word->word[++i])
    {
    	if (set->word->word[i] < '0'  || set->word->word[i] > '9')
        	ft_write_exit(set->word->word, 1);//ПРИ НЕОБХОДИМОСТИ ЗАМЕНИТЬ 1 НА АКТУАЛЬНЫЙ FD
    }
    
   if (set->word->next)
    {
        ft_putendl_fd("e_bash: exit: too many arguments", 1);// не выходит ПРИ НЕОБХОДИМОСТИ ЗАМЕНИТЬ 1 НА АКТУАЛЬНЫЙ FD
        all->error = 1;
        return ;
    }
    //if (set->builtin)
      //  all->error = ft_atoi(set->builtin);
    all->error = ft_atoi(set->word->word) % 256;
    exit(all->error);
}