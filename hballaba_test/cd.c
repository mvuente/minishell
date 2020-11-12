#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>



int main()
{
    int result;
    int fd =1;
    char *path = "testdir";

    result = chdir(path); //return 1 or 0
    if(result != 0)
    {
      write(fd, "cd: no such file or directory: ", 31);
      write(fd, path, strlen(path)); 
    }
      else
        printf("Текущим стал каталог %s\n", path); // потом надо добавить замену PWD и OLDPWD
    return (0);
}