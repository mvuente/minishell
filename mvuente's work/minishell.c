#include "minishell.h"

int     minishell(void)
{
    size_t  ret;
	char	*line;

    write(1, "e_bash!", 7);
    while ((ret = gnl(0, &line)) > 0)
    {  
        
        reader(line);// line came back cause of \n
		free(line);
    }
    if (ret == 0)// (it's if CTRL+D push)
        exit(0);
    read_error();
    return (0);
}