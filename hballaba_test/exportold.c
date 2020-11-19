
#include <stdio.h>
#include "libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
#include <sys/errno.h>



typedef struct	s_env
{
	char *name;
    char *data;
    void *content;
	struct s_env	*next;

}				t_env;




typedef struct s_all
{
    int fd_0;
    int fd_1;
    t_env myenv;
    int error;
    char *home;
    char **path;
}            t_all;

typedef	struct	s_set
{
    char   			*builtin;//comanda
    char			*word;//только эхо
	char			*spec;// спецификатор 
	char			consq;
}				t_set;


typedef	struct	s_genlist
{
	t_set				*set;
	struct	s_genlist	*next;
}				t_genlist;


char *ft_get_value(t_env *myenv, char *name);



t_env	*ft_lstnew_env(char *content)
{
	t_env	*newlist;
    int i;

    i = 0;

	newlist = (t_env*)malloc(sizeof(t_env));
	if (newlist == NULL)
		return (NULL);
    if (ft_strchr(content, '='))
	    newlist->data = ft_strdup((ft_strchr(content, '=') + 1));
    else
        newlist->data = NULL;
    
    newlist->content = content;
    while (content[i] != '=' && content[i])
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

void    ft_free_arr(char **arr)
{
    int i;

    i = -1;
    while (arr[++i])
       free(arr[i]);
    free(arr);   
    }

void    ft_creat_env(char *env[], t_env	**bufenv)
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



void ft_change_data(t_env *tmp, int flag, char *str)
{  
           flag = 1;
           free(tmp->data);
           tmp->data = NULL;
           
           tmp->data = ft_strdup((ft_strchr(str, '=') + 1));
           //printf("%s\n", str);
           
           
           /*if (tmp->content)
            free(tmp->content);
           tmp->content = NULL;
           tmp->content = ft_strjoin_export(tmp->name, "=", tmp->data);
           printf("content %s\n", tmp->content);*/
      
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
		if (bufenv->data)
            content = ft_strjoin_export(bufenv->name, "=", bufenv->data);
        else 
            content = bufenv->name;
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



void ft_add_env(char *str, t_env	*bufenv)
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
   //printf("flag   %d\n", flag);
   if (flag == 0)
        ft_lstadd_back_env(&bufenv, ft_lstnew_env(str)); //если уже есть новую не создает
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

void ft_sort(t_env *bufenv,char **arr, int num)
{
    int i;
    int j;
    char *tmp;
   
   // int a = -1;
    //while (arr[++a])
      //  printf("    %s\n", arr[a]);

   i = -1;
    while (num > ++i)
    {
        j = -1;
        while (++j < num - i)
        {
            if (ft_strncmp(arr[j], arr[j+1], 300) > 0)
             {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
             }
        }
    }

    /*int a = -1;
    while (arr[++a])
      printf("    %s\n", arr[a]);*/
}

void ft_write_export(t_env	*bufenv, int fd, int num)
{
    int i;
    int j;
    char **arr;
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

void ft_write_env(t_env	*bufenv, int fd)
{
    while (bufenv)   // тут возможно надо вернуть одной строкой для перенаправления через pipe
    {   
        if (bufenv->data)
        {
            ft_putstr_fd(bufenv->name, fd);
            ft_putchar_fd('=', fd);
            ft_putendl_fd(bufenv->data, fd);
        }
        bufenv = bufenv->next;
    }
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

int ft_lstsize_pipes(t_genlist *lst)
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

void ft_syscall1(t_env *bufenv, char **arr, char *comanda, char **argv)
{

    pid_t cpid;
    int status;
    char **path;

    //ft_ckeck_syscall()    

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {    /* Потомок читает из канала */
       //close(pipefd[1]);          /* Закрывает неиспользуемый конец для записи */
      
       status = execve(comanda, argv, arr);
       
       //close(pipefd[0]);
       _exit(EXIT_SUCCESS);
    } else {            /* Родитель пишет значение argv[1] в канал */
        //close(pipefd[0]);          /* Закрывает неиспользуемый конец для чтения */
        printf("parents\n");
        //close(pipefd[1]);          /* Читатель видит EOF */
        wait(NULL);                /* Ожидание потомка */
        exit(EXIT_SUCCESS);
    }
}






void ft_init_all(t_all *all, char **env, t_env *bufenv)
{
    all->fd_0 = dup(0);
    all->fd_1 = dup(1);
    ft_creat_env(env, &bufenv);
    all->myenv = *bufenv;
    all->error = 0;
    all->home = getcwd(NULL, 0);
}



void    ft_change_oldpwd(t_env *myenv, char *pwd, char *oldpwd, char *path)
{
    char *tmp;
    int i;
   
    oldpwd = ft_get_value(myenv, "OLDPWD");
    while (myenv)
    {
        if (ft_strncmp(myenv->name, "PWD", 4) == 0 && ft_strlen(myenv->name) == 3 && myenv->data)
        {
            tmp = myenv->data;
            myenv->data = getcwd(NULL, 0);
            free(tmp);
        }
        if (ft_strncmp(myenv->name, "OLDPWD", 7) == 0 && ft_strlen(myenv->name) == 6 && myenv->data)
        {
            tmp = myenv->data;
            myenv->data = ft_strdup(pwd);
            free(tmp);
            free(pwd);
        }
        myenv = myenv->next;
    }
}

char *ft_work_tilda(t_all *all, char *path, char *home)
{
    char *tmp;
    
    tmp = path;
    if (path[1] != '/')
    {
        path = home;
        if (!path)
          path = all->home;
        printf("1%s\n", path);
    }
    else
    {
        if (!home)
            path = ft_strjoin(all->home, path +1);
        else
            path = ft_strjoin(home, path +1);
      printf("2%s\n", path);
    }
     printf("3%s\n", path);
    free(tmp);
    return (path);
}



void ft_write_error(t_all *all, t_set *set, int fd)
{
    all->error = 1;
   // ft_putstr_fd()
    printf("ошибка!!!");


}

char **ft_creat_arr_comanda(char *comanda, t_set *set)
{
    char *tmp;
    char **arr;

    tmp = ft_strjoin_export(comanda, "!", set->spec);
    arr = ft_split(tmp, '!');

   /* int a = -1;
    while (arr[++a])
        printf("%s\n", arr[a]);*/


    free(tmp);

    return (arr);
}

int ft_exit(t_all *all, t_set *set, int fd)
{
   char **arr;
    int i;

    if (ft_strchr(set->builtin, '|'))
        return (0);
    arr = ft_split(set->builtin, ' ');
    i = -1;
    while(arr[0][++i])
    {
       if (!ft_isdigit(arr[0][i]))
       {     
            ft_putstr_fd("bash: exit: ", fd);
            ft_putstr_fd(set->builtin, fd);
            ft_putstr_fd(": numeric argument required", fd);//выходит
            ft_free_arr(arr);
            exit(255);
       }
    }
   if (arr[1])
    {
        ft_putendl_fd("bash: exit: too many arguments", fd);// не выходит
        all->error = 1;
        ft_free_arr(arr);
    }
    if (set->builtin)
        all->error = ft_atoi(set->builtin);
    exit(all->error);
}

char *ft_get_value(t_env *myenv, char *name)
{
    int i; 

    i = ft_strlen(name);
    while (myenv)
        {
            if (ft_strncmp(myenv->name, name, i) == 0 && ft_strlen(myenv->name) == i && myenv->data)
              {
                //printf("\n get_v  %s\n", myenv->data);
                return (myenv->data);
              }
            myenv = myenv->next;
        }
    return(NULL);
}


char *ft_ckeck_syscall(t_env *bufenv, t_set *set, char **arr, char *comanda)
{
    char *path;
    int fd;
    int a;

    fd = 0;

    path = ft_get_value(bufenv, "PATH");

    arr = ft_split(path, ':');
    free(path);

   /* int i = -1;
    while (arr[++i])
        printf(" arr   %s\n", arr[i]);*/


    if (ft_strchr(set->builtin, '/'))
        comanda = set->builtin;
    //printf("path    %s\n", path);
    a = -1;
    while (arr[++a] && !ft_strchr(set->builtin, '/'))
        {
            //printf("    %s\n", arr[a]);
            path = ft_strjoin_export(arr[a], "/", set->builtin);
            //printf("    %s\n", path);
            if ((fd = open(path, O_RDONLY)) > 0)
            {
                comanda = ft_strdup(path);
                close(fd);
                break ;
            }
            free(path);
        }
       // printf("\ncom    %s\n\n", comanda);
    return (comanda);
}

int ft_syscall(t_all *all, t_set *set, t_env *bufenv, int fd)
{
    pid_t cpid;
    int status;
    char *comanda; //с путем
    char **env;
    char **arr;
    
    comanda = NULL;
    env = ft_creat_arr_export(bufenv, ft_lstsize_env(bufenv));
    if (!(comanda = ft_ckeck_syscall(bufenv, set, arr, comanda)))
          ft_write_error(all, set, fd);
    else 
        arr = ft_creat_arr_comanda(comanda, set);

    cpid = fork();
    if (cpid == -1) 
        return (1);

    if (cpid == 0) 
    {    // Потомок читает из канала
     // printf("\ncom    %s\n\n", comanda);
       ft_putstr_fd("hello", 8);
       status = execve(comanda, arr, env);   ///bin/ls, env, ls -la массив 
       
       //printf ("status  %d\n", status);
       //printf ("errno  %d\n", errno);
       //return (0);
       _exit(EXIT_SUCCESS);
    } else 
    {            // Родитель пишет значение argv[1] в канал 
        wait(NULL);                // Ожидание потомка 
        //return (0);
        exit(EXIT_SUCCESS);
    }
    return (0);
}


void    ft_exe_function(t_genlist *pipes, t_all *all, int fd)
{
   // printf("\n%s\n", pipes->set->builtin);
     //printf("%d\n", fd);
    ft_syscall(all, pipes->set, &all->myenv, fd);
   
    
    //здесь надо сделать парсинг для обработки строк с командами
    // после обработки сделать условие для вызова системных или самописных файлов
}

int **ft_init_pipefd(int size)
{
    
    int **pipefd = (int**)malloc(sizeof(int*) * size + 1);
    while (size >= 0)
    {
        pipefd[size] = (int*)malloc(sizeof(int) * 2);
        if (pipe(pipefd[size]) == -1)
            return (0);
       // printf("%d\n", size);
        size--;
    }

    return (pipefd);
}



int ft_work_pipe(t_all *all, t_genlist *pipes, int size, int **pipefd)
{
    pid_t cpid;
    int status;
    int flag;

    flag = 0;     
     if ((cpid = fork())== -1)
        return(1);
        
        if (cpid == 0) 
        { // Потомок читает из канала 0 
           close(pipefd[size][0]); 
           //if (flag == 0)
            dup2(pipefd[size][1], 1); 
           //else 
             //  dup2(pipefd[size][1], pipefd[size+1][1]); 
            flag = 1;
           
           ft_exe_function(pipes, all, 1); // ту вызывается функция которая вызовет или системную или самописную
        } 
        else 
        {   
            close(pipefd[size][1]);         
            dup2(pipefd[size][0], 0);
            waitpid(cpid, &status, WUNTRACED);
           //printf("%d\n", size);
           if (size < 1) // значит что это последня команда и надо вернуть fd в первоначально состояние, чтобы ушло в стдаут терминал
              {
                    dup2(all->fd_1, 1);
            }
           // else
             //  dup2(pipefd[size-1][1], pipefd[size][0]);
            pipes = pipes->next;
            if (size < 1)
               {
                    ft_exe_function(pipes, all, 1);
                     dup2(all->fd_0, 0);
               } 
        }
    return (0);
}


int ft_pipe(t_all *all, t_genlist *pipes, int size)
{
    int **pipefd;
    pid_t cpid;
    int flag;
    int status;
     
    if (!(pipefd = ft_init_pipefd(--size)))
        return (1);
    while (size >= 0)
    {
            printf("size = %d\n", size);
            ft_work_pipe(all, pipes, size, pipefd);
        
        size--;
        pipes = pipes->next;
    }
   return (0);
}




int main(int argc, char *argv[],  char *env[])
{
   
    t_env *bufenv;
    t_all  all;

    char **arr;
    int fd = 1;

    char **arv;
    int num_comand;
    char **arr_comand;
    t_genlist *pipes;
    t_genlist *pipes2;
    t_genlist *pipes3;
    t_genlist *pipes4;

    ft_init_all(&all, env, bufenv);
   // printf("%d\n", all.fd_1);
    //printf("%d\n", all.fd_0);
    
    //int a = -1;
    //while (all.path[++a])
    
     /*t_set set;
     set.builtin = ft_strdup("ls");
     set.spec = ft_strdup("-la");
       // ft_syscall(&all, &set, &all.myenv, 1);*/

    /*pipes = (t_genlist*)malloc(sizeof(t_genlist));
    pipes->set = (t_set*)malloc(sizeof(t_set));
    pipes->set->builtin = ft_strdup("ls");
    pipes->set->spec = ft_strdup("");


    pipes2 = (t_genlist*)malloc(sizeof(t_genlist));
    pipes2->set = (t_set*)malloc(sizeof(t_set));
    pipes2->set->builtin = ft_strdup("cat");
    pipes2->set->spec = ft_strdup("-e");

    pipes->next = pipes2;


    pipes3 = (t_genlist*)malloc(sizeof(t_genlist));
    pipes3->set = (t_set*)malloc(sizeof(t_set));
    pipes3->set->builtin = ft_strdup("cat");
    pipes3->set->spec = ft_strdup("-e");
    pipes3->next = NULL;

    pipes2->next = pipes3;


    pipes4 = (t_genlist*)malloc(sizeof(t_genlist));
    pipes4->set = (t_set*)malloc(sizeof(t_set));
    pipes4->set->builtin = ft_strdup("cat");
    pipes4->set->spec = ft_strdup("-e");
    pipes4->next = NULL;

    pipes3->next = pipes4;
   

    ft_pipe(&all, pipes, (ft_lstsize_pipes(pipes)) - 1);*/
    
    
   // ft_exit(&all, &set, fd);
   
    // char *str = ft_strdup("");

    char *str = ft_strdup("a");
    ft_add_env(str, &all.myenv); //проверить на регистры и невалидные значения
   
    str = ft_strdup("b="); 
    ft_add_env(str, &all.myenv);

    str = ft_strdup("c= asd"); 
    ft_add_env(str, &all.myenv);
    
    str = ft_strdup("A"); 
    ft_add_env(str, &all.myenv);

    str = ft_strdup("a=22"); 
    ft_add_env(str, &all.myenv);

    str = ft_strdup("a="); 
    ft_add_env(str, &all.myenv);
    
   // ft_delete_env("HOME", &all.myenv);

    //char *path = ft_strdup("~/Desctop");

    //ft_cd(&all.myenv, path, 1, &all); // если путь не указан думаю path = NULL


    //ft_write_env(&all.myenv, 1);

    ft_write_export(&all.myenv, 1, ft_lstsize_env(&all.myenv));

    



   /* arr = ft_creat_arr_export(&all.myenv, ft_lstsize_env(&all.myenv));
    int a = -1;
    while (arr[++a])
        printf("    %s\n", arr[a]);*/
    
    //arv = ft_split("ls -la", ' ');
    /*int a = -1;
    while (arv[++a])
        printf("    %s\n", arv[a]);*/

    //arr_comand = ft_split("ls -la,gpep a", ',');
   // ft_syscall(&all.myenv, arr, "/bin/ls", arv);
    

    
      
    return (0);
}