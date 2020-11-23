#include "minishell.h"

char **ft_creat_arr_comanda(char *comanda, t_set *set, char *str)
{
    char *tmp;
    char **arr = NULL;

     //printf("cam  %s\n", comanda);
    //printf("str  %s\n", str);
    if (str)
        {
            tmp = ft_strjoin_export(comanda, "!", str);
            arr = ft_split(tmp, '!');
            free(tmp);
        }
    else
       arr = ft_split(comanda, ' ');
    
    
    return (arr);
}

int ft_write_error(t_all *all, t_set *set, int fd) //доделаю как прикрутим
{
    int error;

    error = 127;
   ft_putstr_fd("bash:", 1);
    ft_putstr_fd(set->builtin, 1);
    ft_putstr_fd(": command not found\n", 1);
  

    return(error);
}

//ft_get_value прикрутить в файл например utils

char *ft_check_syscall(t_env *bufenv, t_set *set, char **arr, char *comanda)
{
    char *path;
    int a;
    int fd;

    fd =0;
    path = ft_get_value(bufenv, "PATH");

    arr = ft_split(path, ':');
   
   // int i = -1;
    //while (arr[++i])
      //  printf(" arr   %s\n", arr[i]);


    if (ft_strchr(set->builtin, '/'))
        comanda = ft_strdup(set->builtin);
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

char *ft_add_str(t_list *word)
{
    char *str;
    t_list *tmp;
    char *tmpstr;

    str = NULL;
    tmp = word;
    if (tmp->word)
        {
            str = ft_strdup(word->word);
            tmp = tmp->next;
        }
    while(tmp)
    {
        //printf("word %s\n", tmp->word);
       tmpstr = str;
       str = ft_strjoin_export(str, "!", tmp->word); 
      // printf("%p\n", tmp->word);

      tmp = tmp->next;
      free(tmpstr);
    }
//printf("%s\n", str);
    return (str);
}

void ft_free_syscall(char *comanda, char **env)
{
        free(comanda);
        ft_free_arr(env);

}

int ft_syscall(t_all *all, t_set *set, t_env *bufenv, int **fd)
{
    pid_t cpid;
    int status;
    char *comanda; //с путем
    char **env;
    char **arr;
    char *str;
    
    str = NULL;
   if (set->word)
      str = ft_add_str(set->word); //создаю строку чтобы получить массив аргументов
    
    comanda = NULL;
    env = ft_creat_arr_export(bufenv, ft_lstsize_env(bufenv));
    
    //ft_check_syscall(bufenv, set, arr, comanda);

    if (!(comanda = ft_check_syscall(bufenv, set, arr, comanda)))
       all->error = ft_write_error(all, set, 1); // Я ЗАМЕНИЛ FD на 1
    else 
      arr = ft_creat_arr_comanda(comanda, set, str);


   cpid = fork();
    if (cpid == -1) 
        return (1);

    if (cpid == 0) 
    {    
       //ft_putstr_fd("hello", 8); // ОН БУДЕТ ПИСАТЬ В ДЕСКРИПТОР 8????? ИЛИ ДЛИНА СЛОВА 8?
       status = execve(comanda, arr, env);   ///bin/ls, env, ls -la массив
      

     exit(status);
    } 
    else 
    {  
         wait(NULL);
    }
     
    //ft_free_arr(arr);
   
    
    //printf("%s\n", comanda);
    ft_free_syscall(comanda, env);
    return (0);
}