#include "minishell.h"

void	ft_change_data(t_env *tmp, int flag, char *str)
{  
    flag = 1;
    free(tmp->data);
    tmp->data = NULL;
          
    if (!(tmp->data = ft_strdup((ft_strchr(str, '=') + 1))))
		malloc_error();
}

void ft_free_set(t_set *set) ///тут надо проверить все ли фришит
{
    while(set->word)
    {
        free(set->word->word);
        set->word = set->word->next;
    }
    
    if (set->builtin)
        free(set->builtin);
    free(set->word);
    free(set);
}