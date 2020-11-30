/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hballaba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 01:22:03 by hballaba          #+#    #+#             */
/*   Updated: 2020/11/30 01:22:05 by hballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"

typedef struct			s_list
{
	char				*word;
	struct s_list		*next;
}						t_list;

typedef struct			s_dirlist
{
	char				*direct;
	char				*fname;
	struct s_dirlist	*next;
}						t_dirlist;

typedef struct			s_env
{
	char				*name;
	char				*data;
	void				*content;
	struct s_env		*next;
}						t_env;

typedef struct			s_all
{
	int					fd_0;
	int					fd_1;
	int					error;
	int					fdstat;
	int					status;
	pid_t				pid;
	char				*home;
	char				*ptr_to_free;
	char				*delimiters;
	char				*quot;
	t_env				*myenv;
}						t_all;

typedef	struct			s_set
{
	char				*builtin;
	t_list				*word;
	t_dirlist			*direct;
	char				spec;
	char				consq;
	int					fd[2];
}						t_set;

typedef	struct			s_genlist
{
	t_set				*set;
	struct s_genlist	*next;
}						t_genlist;

int						g_flag;
int						g_error;

int						minishell(t_all all);
int						*pipe_init(void);
int						is_open_cqs(char *line, char *delimiter, char *quotset);
void					dir_exec(int *fd, t_dirlist *direct, t_all *all);
int						empty_redirect_checker(char *line, char *delimiters);
int						delim_checker(char *line, char *quotset);
int						delim_error(char *delim, int flag);
int						empt_dir_error(void);
int						validator(char *line, t_all *all);
char					*open_cq_error(void);
void					read_error(void);
void					malloc_error(void);
void					ft_pwd(t_all *all);
void					ft_echo(char *name, char *line, char option, \
						char direct);
int						export_executer(t_set *set, t_all *all);
void					executer(t_genlist *genlist, t_all *all, int pipe_flag);
void					reader(char **line, t_all *all);
void					genlstadd(char *delim, t_genlist **genlist);
void					cleargenlist(t_genlist *genlist);
int						ft_cd(t_all *all, t_set *set);
void					ft_free_arr(char **arr);
void					ft_init_all(t_all *all, char **env, t_env *bufenv);
void					ft_creat_env(char *env[], t_env	**bufenv);
void					ft_lstadd_back_env(t_env **lst, t_env *new);
void					ft_change_data(t_env *tmp, int flag, char *str);
void					ft_sort(t_env *bufenv, char **arr, int num);
void					ft_change_oldpwd(t_env *myenv, char *pwd, \
						char *oldpwd, char *path);
int						env_executer(t_set *set, t_all *all);
int						unset_executer(t_set *set, t_all *all);
int						ft_exit(t_all *all, t_set *set);
void					ft_exe_function(t_genlist *pipes, t_all *all, int *fd);
t_env					*ft_lstnew_env(char *content);
int						ft_lstsize_env(t_env *lst);
int						ft_syscall(t_all *all, t_set *set, t_env *bufenv);
int						ft_pipe(t_all *all, t_genlist *pipes, int size);
char					**ft_creat_arr_export(t_env *bufenv, int size);
char					*ft_strjoin_export(char const *s1, char const *s2, \
						char const *s3);
int						pipefinder(t_genlist *genlist);
char					*replace(char **line, char *start, char *finish, \
						char *value);
char					*itemcrtr(char **line, char *finish, int dolflag, \
						t_all all);
char					*tokencrtr(char **line, char *tmp, \
						t_genlist **genlist, t_all *all);
char					*low(char *item);
char					*textpars(char **line, char *tmp, t_set *set, \
						t_all all);
char					*ft_get_value(t_env *myenv, char *var);
char					*dollarpars(char **line, char *ptr, t_all *all);
char					*pipeparser(char **line, char *delim, \
						t_genlist *templist);
char					*semicolparser(char **line, t_genlist **genlist, \
						t_all *all);
char					*cqprocessor(char *item, char **cqptr, int dolflag, \
						t_all all);
char					*cqpars(char **line, char *tmp, char symb, t_all *all);
t_set					wordrcrdr(char *item, t_set set);
char					*dirpars(char **line, char *start, t_set *set, \
						t_all *all);
t_set					builtinrcrdr(char *item, t_set set);
t_dirlist				*dirlistcrtr(char *direction, char *fname);
t_dirlist				*dir_record(t_set *set, char *direct, char *operand);
t_genlist				*initial_genlist(void);
t_list					*ft_create_item(char *data);
t_list					*lstaddback(t_list *word, char *item);
size_t					gnl(int fd, char **line);
int						ft_check_258(t_set *set, t_all *all);
void					ft_free_set(t_set *set);
char					*ft_check_syscall(t_env *bufenv, t_set *set, int fd, \
						int flag);
char					*ft_for_syscall(char *path, int fd, int flag);
char					**ft_creat_arr_comanda(char *comanda, t_set *set, \
						char *str);

#endif
