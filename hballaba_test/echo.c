
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


void ft_echo(char *name, char *line, int option)
{
    int fd;
    if (name)
    {
       // printf("%s\n", name);
        //printf("%s\n", line);
       
        fd = open(name, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
        if (line)
           {
               write(fd, line, strlen(line));
               free(line);
           }
        if (option == 0)
            write(1, "\n", 1);
        close(fd);
        free(name);
    }
    else
    {
        if (line)
            {
                write(1, line, strlen(line));
                free(line);
            }
        if (option == 0)
            write(1, "\n", 1);
        
    }

}



int main(int argc, char **argv)
{
        char *name = strdup("test");
        char *line = strdup("hello");
        int option = 0;
        char *lin1 = NULL;
        char *name1 = NULL;
        ft_echo(name1, line, 0);
    
    return (0);

}