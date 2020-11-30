#include "minishell.h"

t_dirlist	*dirlistcrtr(char *direction, char *fname)
{
	t_dirlist	*direct;

	if (!(direct = (t_dirlist*)malloc(sizeof(t_dirlist))))
		malloc_error();
	direct->direct = direction;
	direct->fname = fname;
	direct->next = NULL;
	return (direct);
}