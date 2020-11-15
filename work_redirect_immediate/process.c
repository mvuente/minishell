#include "minishell.h"

char    *processpars(char **line, char *delim, t_genlist **genlist)
{
   // if (!*genlist)
     //   genlstcrtr(*delim, set, *genlist);
    //else
        genlstadd(delim, genlist);
		*line = delim + 1;
    return (delim + 1);
}