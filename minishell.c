#include "minishell.h"

int     main()
{
    size_t  ret;
	char	*line;

    while ((ret = gnl(0, &line) > 0)
    {  
        shell(parser(line));
		free(line);
    }
    if (ret == 0)
        exit(0);
    read_error();
    return (0);
}