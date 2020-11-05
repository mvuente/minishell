#include "minishell.h"

int     main()
{
    size_t  ret;
	char	*line;

    while ((ret = gnl(0, &line) > 0)
    {  
        shell(parser(line));// line came back cause of \n
		free(line);
    }
    if (ret == 0)// (it's if CTRL+D push)
        exit(0);
    read_error();
    return (0);
}