#include <stdio.h>
#include <unistd.h>

void ft_pwd(void)
{
   char dir[500];
   
    getcwd(dir, 500);
    printf("Current directory is %s\n", dir);
    
}




int main(void)
{
    ft_pwd();



return 0;
}