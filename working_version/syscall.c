#include "minishell.h"

char **ft_creat_arr_comanda(char *comanda, t_set *set, char *str)
{
    char *tmp;
    char **arr;

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

int ft_write_error(t_all *all, t_set *set, char *comanda, char *builtin) //доделаю как прикрутим
{
    int error;

    error = 127;
    if (builtin[0] != '/' && ft_strchr(builtin, '/'))
    {
        ft_putstr_fd("bash:", 1);
        ft_putstr_fd(set->builtin, 1);
        ft_putstr_fd(": No such file or directory\n", 1);

    }
    else
    {
        ft_putstr_fd("bash:", 1);
        ft_putstr_fd(set->builtin, 1);
        ft_putstr_fd(": command not found\n", 1);
    }
    
   
  

    return(error);
}

//ft_get_value прикрутить в файл например utils

char *ft_check_syscall(t_env *bufenv, t_set *set)//сюда вставить fd flag
{
    char *path;
    int a;
    int fd;
    int flag;
    char *comanda;
    char **arr;

    fd =0;
    flag = 0;
    arr = NULL;
    comanda = NULL;
    path = ft_get_value(bufenv, "PATH");
    if (set->builtin[0] == '/' && ft_strchr(set->builtin + 1, '/'))
        comanda = ft_strdup(set->builtin);
    else 
     {
     arr = ft_split(path, ':');
       a = -1;
    while (arr[++a] && !ft_strchr(set->builtin, '/'))
        {
            path = ft_strjoin_export(arr[a], "/", set->builtin);
            if ((fd = open(path, O_RDONLY)) > 0 && flag == 0)
            {
                comanda = ft_strdup(path);
                close(fd);
                flag++;
            }
            free(path);
        }
      ft_free_arr(arr);
     }
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
       tmpstr = str;
       str = ft_strjoin_export(str, "!", tmp->word); 
       tmp = tmp->next;
      free(tmpstr);
    }
    return (str);
}

void ft_free_syscall(char *comanda, char **env, char *str, char **arr)
{
        
        if (str)
            free(str);
        if (comanda)
            free(comanda);
        ft_free_arr(env);
        if (arr)
            ft_free_arr(arr);
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
    arr = NULL;
    comanda = NULL;
   if (set->word)
      str = ft_add_str(set->word); //создаю строку чтобы получить массив аргументов
    env = ft_creat_arr_export(bufenv, ft_lstsize_env(bufenv));
   if (!(comanda = ft_check_syscall(bufenv, set)) || comanda[0] != '/')// не рабоатет при /bin
      all->error = ft_write_error(all, set, comanda, set->builtin);
   else     
    {  
        //printf("arr %s\n", comanda);
        arr = ft_creat_arr_comanda(comanda, set, str);

    }
    
    /*int i =-1;
        while (arr[i])
        printf("arr %s\n", arr[1]);*/

   if ((cpid = fork()) == -1)
         return (1);
   if (cpid == 0) 
    {    
       status = execve(comanda, arr, env);   ///bin/ls, env, ls -la массив
       exit(status);
    } 
    else 
       wait(NULL);
    ft_free_syscall(comanda, env, str, arr);
    return (0);
}