#include "minishell.h"

int     minishell(t_all all)
{
    size_t  ret;
	char	*line;

    write(1, "e_bash!", 7);// current address should be before this line
    while ((ret = gnl(0, &line)) > 0)
    {  
        
        reader(line, all);// line came back cause of \n
		free(line);
    }
    if (ret == 0)// (it's if CTRL+C push)
        exit(0);
    read_error();
    return (0);
}