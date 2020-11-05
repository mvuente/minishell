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
void	command_error(void);
void	shell(t_set **set);
char	*textpars(char **line, char *tmp);
char	*cqpars(char *tmp, char symb);
char    *backpars(char *tmp);
t_set	**parser(char *line);
size_t	gnl(int fd, char **line);

# endif