#include "minishell.h"

void    ft_change_oldpwd(t_env *myenv, char *pwd, char *oldpwd, char *path)
{
    char *tmp;
    int i;
    char *tmp_pwd;

    while (myenv)
    {
        if (ft_strncmp(myenv->name, "PWD", 4) == 0 && myenv->data)
        {
            tmp = myenv->data;
            if (!(myenv->data = ft_strdup(path)))
				malloc_error();
            free(tmp);
        }
        if (ft_strncmp(myenv->name, "OLDPWD", 7) == 0 && myenv->data)
        {
            tmp = myenv->data;
            if (!(myenv->data = ft_strdup(pwd)))
				malloc_error();
            free(tmp);
        }
        myenv = myenv->next;
    }
}

void ft_cd(t_all *all, char *path)
{
    int result;
    char *home;
    char *oldpwd;
    char *pwd;
   
    pwd = ft_get_value(all->myenv, "PWD");
    oldpwd = ft_get_value(all->myenv, "OLDPWD");
    home = ft_get_value(all->myenv, "HOME");
    if (!path)
        path = home;
    result = chdir(path); //return -1 or 0
    if(result != 0)
    {
    	write(1, "cd: ", 4); 
    	write(1, path, ft_strlen(path));
    	write(1, " no such file or directory", 26);
    }
    else
    {
        ft_change_oldpwd(all->myenv, pwd, oldpwd, path);
        write(1, " /", 2);
		write(1, all->myenv->data, ft_strlen(all->myenv->data));
    }
	write(1, "\n", 1);
    return ;
}