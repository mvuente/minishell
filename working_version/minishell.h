#ifndef minishell_h
# define minishell_h

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct s_list
{
    char            *word;
    struct s_list   *next;
}               t_list;


typedef struct	s_env
{
	char *name;
    char *data;
    void *content;
	struct s_env	*next;

}				t_env;

typedef struct s_all
{
    int fd_0;
    int fd_1; 
    //char *path;
    //char *home;
    t_env *myenv;

}               t_all;

typedef	struct	s_set
{
    char   			*builtin;
    t_list			*word;
	char			spec;
	char			consq;
}				t_set;

typedef	struct	s_genlist
{
	t_set				*set;
	struct	s_genlist	*next;
}				t_genlist;

int		minishell(t_all all);
int     **dir_exec(int **fd, char *operator, char *operand);
void	read_error(void);
void	malloc_error(void);
void	command_error(void);
void	ft_pwd(int **fd, t_all *all);
void 	ft_echo(char *name, char *line, char option, char direct);
void	export_executer(t_set *set, int **fd, t_all *all);
void	executer(t_genlist *genlist, int **fd, t_all *all);
void	reader(char *line, t_all all);
void	genlstadd(char *delim, t_genlist **genlist);

void	ft_cd(t_all *all, char *path);
void    ft_free_arr(char **arr);
void	ft_init_all(t_all *all, char **env, t_env *bufenv);
void    ft_creat_env(char *env[], t_env	**bufenv);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	ft_change_data(t_env *tmp, int flag, char *str);
void	ft_sort(t_env *bufenv, char **arr, int num);
void    ft_change_oldpwd(t_env *myenv, char *pwd, char *oldpwd, char *path);
void	env_executer(t_set *set, int **fd, t_all *all);
void	unset_executer(t_set *set, int **fd, t_all *all);
t_env	*ft_lstnew_env(char *content);
int	    ft_lstsize_env(t_env *lst);
char	**ft_creat_arr_export(t_env *bufenv, int size);




char	*replace(char **line, char *start, char *finish, char *value);
//void	shell(t_set **set);
char	*itemcrtr(char **line, char *tmp);
char	*tokencrtr(char **line, char *tmp, t_genlist **genlist, int **fd);
char	*low(char *item);
char	*textpars(char **line, char *tmp, t_set *set);
char    *processpars(char **line, char *delim, t_genlist **genlist);
char	*cqpars(char *tmp, char symb);
char	*ft_get_value(t_env *myenv, char *var);
char	*dollarpars(char **line, char *ptr, t_all all);
//char    *backpars(char *tmp);
t_set	wordrcrdr(char *item, t_set set);
char	*dirpars(char **line, char *start, int **fd);
t_set	builtinrcrdr(char *item, t_set set);
t_genlist	*initial_genlist(void);
//t_set	**parser(char *line);
t_list	*ft_create_item(char *data);
t_list	*lstaddback(t_list *word, char *item);
size_t	gnl(int fd, char **line);

# endif
