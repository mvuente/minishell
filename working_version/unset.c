#include "minishell.h"

void (ft_no_valid_word_unset(char *word))
{
    ft_putstr_fd("bash: unset: `", 1);
    ft_putstr_fd(word, 1);
    ft_putstr_fd("': not a valid identifier\n", 1);
}

int ft_delete_env(char *str, t_env	*bufenv)
{
    int i;
    int flag;
    t_env *tmp;
    void *ptr;
    
    i = ft_strlen(str);
    flag =0;
    while (bufenv->next)
    {
        if(ft_strncmp(bufenv->name, str, i) == 0 && i == ft_strlen(bufenv->name))
        {
            flag = 1;
            tmp->next = bufenv->next;
            free(bufenv->data);
            free(bufenv->name);
            free(bufenv);
        }
        if (flag == 1)
            break ;
       tmp = bufenv;
       bufenv = bufenv->next;
    }
    if (flag == 0)
        return (1);
    return (0);
}

int ft_check_word_unset(char *word)
{
    int i;
    char c;
    int flag;

    flag = 0;
    i = -1;
    if (word[0] >= '0' && word[0] <= '9')
        return (0);
    while (word[++i])
    {
        c = word[i];
        if ((c >= '*' && c <= '/') || (c >= ':' && c <= '@') || (c >= '{' && c <= '~'))
            return (1);
    }
    return (0);
}

static int		ft_check_258(t_set *set, t_all *all) /// ee можно добавить в общие ее использует unset
{
    t_list *tmp;
    tmp = set->word;

    while(tmp)
    {
        if (ft_strchr(tmp->word, '(') || ft_strchr(tmp->word, ')'))
        {
            if (tmp->word[0] == '(' && !tmp->word[1])
                ft_putendl_fd("bash: syntax error near unexpected token `newline'", 1);
            else if (tmp->word[0] == '(' && tmp->word[1])
            {
                ft_putstr_fd("bash: syntax error near unexpected token `", 1);
                ft_putstr_fd(++tmp->word, 1);
                ft_putendl_fd("'", 1);
            }
            else if (ft_strchr(tmp->word, '('))
                ft_putendl_fd("bash: syntax error near unexpected token `('", 1);
            else if (ft_strchr(tmp->word, ')'))
                ft_putendl_fd("bash: syntax error near unexpected token `)'", 1);
            all->error = 258;
            return (0);
        }
        tmp = tmp->next;
    }

       return (1);
}

void	unset_executer(t_set *set, int **fd, t_all *all) // FD НЕ НУЖЕН???
{
    int check;
    int flag;

    flag = 0;
    if (!ft_check_258(set, all))
    	return ;
	   //return (258);
    while(set->word)
    {
       	check = ft_check_word_unset(set->word->word);
       	if (check == 1)
        {
            ft_no_valid_word_unset(set->word->word);
            all->error = 1;
            flag = 1;
        }
       	else 
            ft_delete_env(set->word->word, all->myenv);
      	set->word = set->word->next;
    }
    if (flag == 1)
		return ;
		//return (1);
    return ;
	//return (0);
}