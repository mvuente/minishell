#include "minishell.h"

void    ft_change_oldpwd(t_env *myenv, char *pwd, char *oldpwd, char *path)
{
    char *tmp;
    int i;
    char *tmp_pwd;

    printf("pwd = %s\n", pwd);

    oldpwd = ft_get_value(myenv, "OLDPWD");
    while (myenv)
    {
        if (ft_strncmp(myenv->name, "PWD", 4) == 0 && ft_strlen(myenv->name) == 3 && myenv->data)
        {
            if (ft_strncmp(myenv->name, "PWD", 4) == 0 && ft_strlen(myenv->name) == 3 && myenv->data)
            {
                tmp = myenv->data;
                myenv->data = getcwd(NULL, 0);//ft_strdup(path);
                free(tmp);
            }
             /*if (ft_strncmp(myenv->name, "OLDPWD", 7) == 0 && ft_strlen(myenv->name) == 6 && myenv->data)
            {
                tmp = myenv->data;
                myenv->data = ft_strdup(pwd);
                free(tmp);
            }*/
            myenv = myenv->next;
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

void ft_cd(t_all *all, t_set *set)
{
    int result;
    char *home;
    char *oldpwd;
    char *pwd;
    char *path;

    oldpwd = ft_get_value(all->myenv, "OLDPWD");
    pwd = getcwd(NULL, 0);
    home = ft_get_value(all->myenv, "HOME");

    if (set->word)
        path = set->word->word;
    else
    {      
        path = home;
        if (!path)
          path = all->home;
    }

   // result = chdir(path); //return 1 or 0
    //if(result != 0)

    if (path[0] == '~')//возможно не надо отрабатывать
       path = ft_work_tilda(all, path, home);
     //printf("%s\n", path);
    if ((chdir(path)) != 0) //return 1 or 0
    {
      write(1, "cd: no such file or directory: ", 31);
      write(1, "cd: ", 4);
      write(1, path, ft_strlen(path));
      ft_putendl_fd(": No such file or directory", 1);
      return ;//(1);
    }
    else
    {
        ft_change_oldpwd(all->myenv, pwd, oldpwd, path);
        //printf("Текущим стал каталог %s\n", path); // потом надо добавить замену PWD и OLDPWD
    }
       // ft_change_oldpwd(all->myenv, pwd, NULL, path);
    //return (0);*/
}