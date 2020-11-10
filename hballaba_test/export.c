
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


int main(int argc, char *argv[], char *env[])
{
    t_env	*bufenv;
    t_env *myenv;
    
    int t = -1;
    int size;
    while (env[++t])
       ft_lstadd_back_env(&bufenv, ft_lstnew_env(env[t]));
    //size = ft_lstsize(bufenv);
    //printf("size %d\n",size);
        
    

    while (bufenv->next)
    {
        printf("name  %s\n", bufenv->name);
        printf("data  %s\n", bufenv->data);
        printf("cont  %s\n", bufenv->content);
    
        
        bufenv = bufenv->next;

      
    }
    //printf("%s\n", bufenv->content);
    return 0;
}