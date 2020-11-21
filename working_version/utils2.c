#include "minishell.h"

void	ft_change_data(t_env *tmp, int flag, char *str)
{  
    flag = 1;
    free(tmp->data);
    tmp->data = NULL;
          
    if (!(tmp->data = ft_strdup((ft_strchr(str, '=') + 1))))
		malloc_error();
}

void	ft_free_set(t_set *set) ///тут надо проверить все ли фришит
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