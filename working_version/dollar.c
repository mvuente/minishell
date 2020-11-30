#include "minishell.h"

char	*replace(char **line, char *start, char *finish, char *value)
{
	size_t	delta;
	char	*tmpline;
	char	*newline;
	
	printf("BEFORE start is %s\n", start);
	printf("BEFORE start adress is %p\n", start);
	printf("BEFORE *line adress is %p\n", *line);
	if (value)
		delta = ft_strlen(value) - (finish - start);
	else
		delta = start - finish;
	printf("delta is %i\n", (int)delta);
	if (!(newline = (char*)ft_calloc(ft_strlen(*line) + delta + 1, sizeof(char))))
		malloc_error();
	printf("before I make newline, *line is %s and # of symbols is %i\n", *line, (int)(start + 1 - *line));
	newline = ft_memmove(newline, *line, start - *line);
	tmpline = newline + ft_strlen(newline);
	printf("I've JUST made newline and it is %s\n", newline);
	printf("I've moved tmpline to and it is %s\n", tmpline);
	if (value)
	{
		tmpline = ft_memmove(tmpline, value, ft_strlen(value));
		tmpline = tmpline + ft_strlen(value);
	}
	if (*(finish - 1) == 0x3f)
	{
		printf("value adress is %p\n", value);
		free(value);
	}
	printf("BEFORE FINAL tmpline is %s AND finish is %s\n", tmpline, finish);
	tmpline = ft_memmove(tmpline, finish, ft_strlen(finish) + 1);
	//printf("tmpline adress is %s\n", tmpline);
	printf("newline adress is %p\n", newline);
	
	//free(*line);
	*line = newline;
	//printf("AFTER *line adress is %p\n", *line);
	
	return (tmpline);
}

void	ft_putnbr_fd(int n, int fd)                                   /////добавил функцию
{
	long long int number;

	number = n;
	if (number < 0)
	{
		write(fd, "-", 1);
		number = number * -1;
	}
	if (number > 9)
	{
		ft_putnbr_fd(number / 10, fd);
		ft_putnbr_fd(number % 10, fd);
	}
	else
		ft_putchar_fd(number + 48, fd);
}


char	*dollarpars(char **line, char *ptr, t_all *all)
{
	char	*var;
	char	*tmp;
	char	*value;
	char	*res;

	ptr = ft_memmove(ptr, ptr + 1, ft_strlen(ptr + 1) + 1);// просто сдвинут всю строку на 1 влево, убрав $
	tmp = ptr;
	//printf("ptr is %s\n", ptr);
	if (*tmp && *tmp == 0x3f)
	{
		if (!(value = ft_itoa(errno)))
			malloc_error();
		//ptr--;
		tmp++;
		errno = 0;
		res = (replace(line, ptr, tmp, value));// заменить кусок строки от ptr до tmp на это значение
		free(all->ptr_to_free);
		all->ptr_to_free = *line;
		return (res);
	}
	else if (*tmp && ft_isdigit(*tmp))
		return (tmp = ft_memmove(tmp, tmp + 1, ft_strlen(tmp + 1) + 1));
	else
	{
		while (tmp && (ft_isalnum(*tmp) || *tmp == 0x5f))
			tmp++;
		var = itemcrtr(&ptr, tmp, 0, *all); //получил имя перменной окружения
		value = ft_get_value(all->myenv, var);//взять значение переменной
		//printf("PTR before restatemnet is %s\n", ptr);
		ptr = ptr - ft_strlen(var); // вернул указатель на место
		//printf("PTR after restatemnet is %s\n", ptr);
		free(var);
	}
	res = (replace(line, ptr, tmp, value));// заменить кусок строки от ptr до tmp на это значение
	free(all->ptr_to_free);
	all->ptr_to_free = *line;
	return (res);
}