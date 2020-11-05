#ifndef minishell_h
# define minishell_h

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef	struct	s_set
{

}				t_set

void	read_error(void);
void	malloc_error(void);
void	shell(t_set **set);
t_set	**parser(char *line);
size_t	gnl(int fd, char **line);

# endif