#include "minishell.h"

//void ft_free_set(t_set *set)
//{
//    while(set->word)
//    {
//        free(set->word->word);
//        set->word = set->word->next;
 //   }
//    
//    if (set->builtin)
//        free(set->builtin);
//    free(set->word);
//    free(set);
//}

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
   free(name);
   if (flag == 0)
        ft_lstadd_back_env(&bufenv, ft_lstnew_env(str)); //если уже есть новую не создает
}

void	ft_write_export(t_env *bufenv, int fd, int num)
{
    int i;
    int j;
    char **arr;
    //printf("%d\n", num);
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

int ft_check_word_export(char *word)
{
    int i;
    char c;
    int flag;

    flag = 0;
    i = -1;
    c = word[0];
    if ((c  >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        c = word[0];
    else if (c == '_' && !word[1])
        return (2);
    else
    {
    	//printf("errno is %i\n", errno);
		errno = 1; // не уверен
		return (0);
	}
    return (1);
}

void ft_no_valid_word(char *word)
{
    ft_putstr_fd("bash: export: `", 1);
    ft_putstr_fd(word, 1);
    ft_putstr_fd("': not a valid identifier\n", 1);
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

void	export_executer(t_set *set, int **fd, t_all *all)
{
	int check;
   
     if (!ft_check_258(set, all))
    	return ;
	   //return (258);
	//printf("arg is %s\n", mytemp->word);
	if (!set->word)
		ft_write_export(all->myenv, 1, ft_lstsize_env(all->myenv));
	else
		{
            
         while(set->word)
            {
               //write(1, "he\n", 3);
               check = ft_check_word_export(set->word->word);
                if (check == 1)
                    ft_add_env(set->word->word, all->myenv);
                else if (check == 2)
                    continue ;
                else
                    ft_no_valid_word(set->word->word);
                
                set->word = set->word->next;
            }
        }
        ft_free_set(set);
}
