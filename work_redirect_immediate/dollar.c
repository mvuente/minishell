#include "minishell.h"

char	*replace(char **line, char *start, char *finish, char *value)
{
	size_t	delta;
	char	*tmpline;
	char	*newline;
	
	if (value)
		delta = ft_strlen(value) - (tmp - ptr);
	else
		delta = ptr - tmp;
	if (!(newline = (char*)ft_calloc(ft_strlen(*line) + delta + 1, sizeof(char))))
		malloc_error();
	newline = ft_memmove(newline, *line, start + 1 - *line);
	tmpline = newline + ft_strlen(newline);
	if (value)
	{
		tmpline = ft_memmove(tmpline, value, ft_strlen(value));
		tmpline = tmpline + ft_strlen(value);
	}
	tmpline = ft_memmove(tmpline, finish, ft_strlen(finish);
	free(*line);
	*line = newline;
	return (tmpline);
}

char	*dollarpars(char **line, char *ptr, t_all all)
{
	char	*var;
	char	*tmp;
	char	*value;

	ptr = ft_memmove(ptr, ptr + 1, ft_strlen(ptr + 1) + 1);// просто сдвинут всю строку на 1 влево, убрав $
	tmp = ptr;
	while (ft_isalnum(*tmp) || *tmp == 0x5f)
		tmp++;
	var = itemcrtr(&ptr, tmp); //получил имя перменной окружения
	ptr = ptr - ft_strlen(var) - 1; // вернул указатель на место
	value = ft_get_value(all->myenv, var);//взять значение переменной
	return (replace(line, ptr, tmp, value));// заменить кусок строки от ptr до tmp на это значение
}