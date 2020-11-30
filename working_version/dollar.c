#include "minishell.h"

char	*qwest_proc(char **line, char *tmp, char *ptr, t_all *all)
{
	char	*value;
	char	*res;

	if (!(value = ft_itoa(errno)))
		malloc_error();
	tmp++;
	errno = 0;
	res = (replace(line, ptr, tmp, value));
	free(all->ptr_to_free);
	all->ptr_to_free = *line;
	return (res);
}

char	*replace(char **line, char *start, char *finish, char *value)
{
	size_t	delta;
	char	*tmpline;
	char	*newline;

	if (value)
		delta = ft_strlen(value) - (finish - start);
	else
		delta = start - finish;
	if (!(newline = (char*)ft_calloc(ft_strlen(*line) + delta + 1, \
	sizeof(char))))
		malloc_error();
	newline = ft_memmove(newline, *line, start - *line);
	tmpline = newline + ft_strlen(newline);
	if (value)
	{
		tmpline = ft_memmove(tmpline, value, ft_strlen(value));
		tmpline = tmpline + ft_strlen(value);
	}
	if (*(finish - 1) == 0x3f)
		free(value);
	tmpline = ft_memmove(tmpline, finish, ft_strlen(finish) + 1);
	*line = newline;
	return (tmpline);
}

char	*dollarpars(char **line, char *ptr, t_all *all)
{
	char	*var;
	char	*tmp;
	char	*value;
	char	*res;

	ptr = ft_memmove(ptr, ptr + 1, ft_strlen(ptr + 1) + 1);
	tmp = ptr;
	if (*tmp && *tmp == 0x3f)
		return (qwest_proc(line, tmp, ptr, all));
	else if (*tmp && ft_isdigit(*tmp))
		return (tmp = ft_memmove(tmp, tmp + 1, ft_strlen(tmp + 1) + 1));
	else
	{
		while (tmp && (ft_isalnum(*tmp) || *tmp == 0x5f))
			tmp++;
		var = itemcrtr(&ptr, tmp, 0, *all);
		value = ft_get_value(all->myenv, var);
		ptr = ptr - ft_strlen(var);
		free(var);
	}
	res = (replace(line, ptr, tmp, value));
	free(all->ptr_to_free);
	all->ptr_to_free = *line;
	return (res);
}
