#include "minishell.h"

char **ft_creat_arr_comanda(char *comanda, t_set *set)
{
    char *tmp;
    char **arr;

   // tmp = ft_strjoin_export(comanda, "!", set->spec);
    arr = ft_split(tmp, '!');
    free(tmp);
    return (arr);
}

void ft_write_error(t_all *all, t_set *set, int fd) //доделаю как прикрутим
{
    all->error = 1;
   // ft_putstr_fd()
    printf("ошибка!!!");


}

//ft_get_value прикрутить в файл например utils

/*char *ft_check_syscall(t_env *bufenv, t_set *set, char **arr, char *comanda)
{
    char *path;
    int fd;
    int a;

    fd = 0;

    path = ft_get_value(bufenv, "PATH");

    arr = ft_split(path, ':');
    free(path);

   // int i = -1;
    //while (arr[++i])
      //  printf(" arr   %s\n", arr[i]);


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
}*/

char *ft_add_str(t_list *word)
{
    char *str;
    t_list *tmp;
    char *tmpstr;

    tmp = word;
    str = ft_strdup("");
    while(tmp)
    {
       // printf("%s\n", tmp->word);
       tmpstr = str;
       ft_strjoin_export(str, " ", tmp->word); 
       //printf("%s\n", str);

      tmp = tmp->next;
      free(tmpstr);
    }
printf("%s\n", str);
    return (str);
}

int ft_syscall(t_all *all, t_set *set, t_env *bufenv, int **fd)
{
    pid_t cpid;
    int status;
    char *comanda; //с путем
    char **env;
    char **arr;
    char *str;

    str = ft_add_str(set->word); //создаю строку чтобы получить массив аргументов
   // printf("%s\n", str);
   /* comanda = NULL;
    env = ft_creat_arr_export(bufenv, ft_lstsize_env(bufenv));
    if (!(comanda = ft_check_syscall(bufenv, set, arr, comanda)))
          ft_write_error(all, set, 1); // Я ЗАМЕНИЛ FD на 1
    else 
        arr = ft_creat_arr_comanda(comanda, set);

    cpid = fork();
    if (cpid == -1) 
        return (1);

    if (cpid == 0) 
    {    // Потомок читает из канала
     // printf("\ncom    %s\n\n", comanda);
       ft_putstr_fd("hello", 8); // ОН БУДЕТ ПИСАТЬ В ДЕСКРИПТОР 8????? ИЛИ ДЛИНА СЛОВА 8?
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
    }*/
    return (0);
}