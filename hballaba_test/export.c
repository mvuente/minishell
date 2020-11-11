
#include <stdio.h>
#include "libft.h"



typedef struct	s_env
{
	char *name;
    char *data;
    void *content;
	struct s_env	*next;
}				t_env;

t_env	*ft_lstnew_env(char *content)
{
	t_env	*newlist;
    int i;

    i = 0;

	newlist = (t_env*)malloc(sizeof(t_env));
	if (newlist == NULL)
		return (NULL);
	newlist->data = ft_strdup((ft_strchr(content, '=') + 1));
    newlist->content = content;
    while (content[i] != '=')
      i++;
    newlist->name = ft_calloc(sizeof(char), i + 1);
    ft_strlcpy(newlist->name, content, i + 1);
   	newlist->next = NULL;
	return (newlist);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*buffer;

	if (!new)
		return ;
	if (*lst)
	{
		buffer = *lst;
		while (buffer->next)
		    buffer = buffer->next;
		buffer->next = new;
	}
	else
		*lst = new;
}

void    ft_creat_export(char *env[], t_env	**bufenv)
{
   int t = -1;

    while (env[++t])
        ft_lstadd_back_env(bufenv, ft_lstnew_env(env[t]));
}

/*void ft_change_data(char *name, char *str, t_env *bufenv, int i)
{  

   // printf("%d\n", i);
    //printf("%s\n", name);
   while (bufenv->next)
   {
        if (ft_strncmp(bufenv->name, name, i) == 0 && i == ft_strlen(bufenv->name))
        {
           free(bufenv->data);
           bufenv->data = ft_strdup((ft_strchr(str, '=') + 1));
          // printf("%s\n", name);
        }
        bufenv = bufenv->next;
   }
   if (ft_strncmp(bufenv->name, name, i) == 0 && i == ft_strlen(bufenv->name))
        {
           free(bufenv->data);
           //bufenv->data = ft_strdup((ft_strchr(str, '=') + 1));
           //printf("%s\n", name);
            //printf("%s\n", bufenv->data);
        }
}*/


void ft_add_export(char *str, t_env	**bufenv)
{
   t_env *tmp;
   int flag;
   int i;
   char *name;
   
   flag = 0;
   tmp = *bufenv;
   i = 0;
   while (str[i] != '=')
    i++;
   name = ft_calloc(sizeof(char), i + 1);
   ft_strlcpy(name, str, i + 1);
   while (tmp)
   {
        if (ft_strncmp(tmp->name, name, i) == 0 && i == ft_strlen(tmp->name))
        {
           flag = 1;
           free(tmp->data);
           tmp->data = NULL;
           tmp->data = ft_strdup((ft_strchr(str, '=') + 1));    
        }
        tmp = tmp->next;
   }
   if (flag == 0)
        ft_lstadd_back_env(bufenv, ft_lstnew_env(str)); //если уже есть новую не создает
}

int ft_delete_export(char *str, t_env	*bufenv)
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

void ft_write_export(t_env	*bufenv, int fd)
{
    while (bufenv)   // тут возможно надо вернуть одной строкой для перенаправления через pipe
    {   
        ft_putstr_fd(bufenv->name, fd);
        ft_putchar_fd('=', fd);
        ft_putendl_fd(bufenv->data, fd);
        bufenv = bufenv->next;
    }
}

int main(int argc, char *argv[], char *env[])
{
   
    t_env *bufenv;
        
    ft_creat_export(env, &bufenv);
    ft_add_export("hello=111", &bufenv); //проверить на регистры и невалидные значения
    ft_add_export("hello=222", &bufenv);
  
    ft_add_export("hello2=poka2", &bufenv);
    ft_delete_export("hello", bufenv);
    ft_write_export(bufenv, 1);
      
    return 0;
}