
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


char	*ft_strjoin_export(char const *s1, char const *s2, char const *s3)
{
	char	*str;
	size_t	lens1;
	size_t	lens2;
    size_t	lens3;

	lens1 = ft_strlen((char*)s1);
	lens2 = ft_strlen((char*)s2);
    lens3 = ft_strlen((char*)s3);
	str = (char*)malloc(lens1 + lens2 + lens3+ 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, lens1 + 1);
	ft_strlcat(str, s2, lens2 + lens1 + 1);
    ft_strlcat(str, s3, lens3 + lens2 + lens1 + 1);
	return (str);
}



void ft_change_data(t_env *tmp, int *flag, char *str)
{  
           *flag = 1;
           free(tmp->data);
           tmp->data = NULL;
           tmp->data = ft_strdup((ft_strchr(str, '=') + 1));
           /*if (tmp->content)
            free(tmp->content);
           tmp->content = NULL;
           tmp->content = ft_strjoin_export(tmp->name, "=", tmp->data);
           printf("content %s\n", tmp->content);*/
      
}


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
           ft_change_data(tmp, &flag, str);
           //flag = 1;
           //free(tmp->data);
           //tmp->data = NULL;
           //tmp->data = ft_strdup((ft_strchr(str, '=') + 1));    
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

char **ft_creat_arr_export(t_env *bufenv, int size)
{
   char **arr;
   int i;
   char *content;

   i = 0;
   arr = (char**)malloc(sizeof(char*) * (size + 1));
   if (!arr)
        return(0); //free malloc
    while (bufenv)
	{
		content = ft_strjoin_export(bufenv->name, "=", bufenv->data);
        arr[i] = (char*)malloc(sizeof(char) * (ft_strlen(content) + 1));
		if (!arr[i])
			return(0); //free maloc
		ft_memcpy(arr[i], content, ft_strlen(content) + 1);
		bufenv = bufenv->next;
		i++;
	}
	arr[i] = NULL;

    


    return (arr);
}

int ft_lstsize_env(t_env *lst)
{
    int i;

	if (!lst)
		return (0);
	i = 1;
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}


void ft_syscall(t_env *bufenv, char **arr, char *comanda, char **argv)
{

    int pipefd[2];
    pid_t cpid;

    if (pipe(pipefd) == -1) 
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {    /* Потомок читает из канала */
       close(pipefd[1]);          /* Закрывает неиспользуемый конец для записи */
      
       execve(comanda, argv, arr);
       
       close(pipefd[0]);
       _exit(EXIT_SUCCESS);
    } else {            /* Родитель пишет значение argv[1] в канал */
        close(pipefd[0]);          /* Закрывает неиспользуемый конец для чтения */
        printf("parents\n");
        close(pipefd[1]);          /* Читатель видит EOF */
        wait(NULL);                /* Ожидание потомка */
        exit(EXIT_SUCCESS);
    }



}


int main(int argc, char *argv[],  char *env[])
{
   
    t_env *bufenv;
    char **arr;

    char **arv;
        
    ft_creat_export(env, &bufenv);
    ft_add_export("hello=111", &bufenv); //проверить на регистры и невалидные значения
    ft_add_export("hello=222", &bufenv);
  
    ft_add_export("hello2=poka2", &bufenv);
    //ft_delete_export("hello", bufenv);
    //ft_write_export(bufenv, 1);
    arr = ft_creat_arr_export(bufenv, ft_lstsize_env(bufenv));
    /*int a = -1;
    while (arr[++a])
        printf("    %s\n", arr[a]);*/
    
    arv = ft_split("ls -la", ' ');
    /*int a = -1;
    while (arv[++a])
        printf("    %s\n", arv[a]);*/
    ft_syscall(bufenv, arr, "/bin/ls", arv);
      
    return 0;
}