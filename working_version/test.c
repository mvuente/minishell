#include "minishell.h"

//int main()
//{
  //  minishell();
   // printf("the end");
    //return (0);
//}

int main(int argc, char *argv[],  char *env[])
{
    t_env *bufenv;
    t_all  all;
    char **arr;
    char **arv;
    int num_comand;
    char **arr_comand;

    ft_init_all(&all, env, bufenv);
    minishell(all);
    //char *path = ft_strdup("");
    //ft_cd(&all.myenv, NULL, 1); // если путь не указан думаю path = NULL
    //ft_write_env(&all.myenv, 1);
     return 0;
}