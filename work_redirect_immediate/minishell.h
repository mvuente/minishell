#ifndef minishell_h
# define minishell_h

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"



typedef	struct	s_set
{
    char   			*builtin;
    char			*word;
	char			spec;
	char			consq;
}				t_set;

typedef	struct	s_genlist
{
	t_set				*set;
	struct	s_genlist	*next;
}				t_genlist;

int		minishell(void);
int     **dir_exec(int **fd, char *operator, char *operand);
void	read_error(void);
void	malloc_error(void);
void	command_error(void);
void	ft_pwd(void);
void 	ft_echo(char *name, char *line, char option, char direct);
void	executer(t_genlist *genlist, int **fd);
void	reader(char *line);
void	genlstadd(char *delim, t_genlist **genlist);
//void	shell(t_set **set);
char	*itemcrtr(char **line, char *tmp);
char	*tokencrtr(char **line, char *tmp, t_genlist **genlist, int **fd);
char	*low(char *item);
char	*textpars(char **line, char *tmp, t_set *set);
char    *processpars(char **line, char *delim, t_genlist **genlist);
char	*cqpars(char *tmp, char symb);
//char    *backpars(char *tmp);
t_set	wordrcrdr(char *item, t_set set);
char	*dirpars(char **line, char *start, int **fd);
t_set	builtinrcrdr(char *item, t_set set);
t_genlist	*initial_genlist(void);
//t_set	**parser(char *line);
//t_list	*ft_create_item(char *data);
//t_list	*lstaddfront(t_list *word, char *item);
size_t	gnl(int fd, char **line);

# endif