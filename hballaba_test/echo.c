
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


void ft_echo_doubledir(char *name, char *line, int option)
{
     int fd;

    fd = 1;
    if (name)
       fd = open(name, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
    if (line)
    {
        write(fd, line, strlen(line));
        free(line);
    }
    if (option == 0)
       write(fd, "\n", 1);     
    free(name);
}

void ft_echo_dir(char *name, char *line, int option)
{
    int fd;

    fd = 1;
    if (name)
       fd = open(name, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
    if (line)
    {
        write(fd, line, strlen(line));
        free(line);
    }
    if (option == 0)
       write(fd, "\n", 1);     
    free(name);
}

void ft_echo_backdir(char *name, char *line, int option)
{
    int oldfd;
    int newfd;

    oldfd = open(name, O_RDONLY);
    if (oldfd == -1)
    {
        write(1, name, strlen(name));
        write(1, ": No such file or directory\n", 28);
        return ;
    }
    dup2(oldfd, newfd);

    close(oldfd);

}

void ft_echo(char *name, char *line, int option, char direct)
{
    if (direct == '^')
        ft_echo_doubledir(name, line, option);
    if (direct == '>')
        ft_echo_dir(name, line, option);
    if (direct == '<')
        ft_echo_backdir(name, line, option);
}


int main(int argc, char **argv)
{
        char *name = strdup("test1");
        char *line = strdup("hello");
        int option = 0;
        char *line1 = NULL;
        char *name1 = NULL;

        int direct = 0;
        ft_echo(name, line, 0, '<');
    
    return (0);
}