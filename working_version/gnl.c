#include "minishell.h"

static	char	*bufrecorder(char *tmp, char buf)
{
	char	*old;
	size_t	length;

	old = tmp;
	length = ft_strlen(old);
	if (!(tmp = (char*)malloc(sizeof(char) * length + 2)))
		malloc_error();
	ft_bzero(tmp, length + 2);
	ft_memmove(tmp, old, length);
	tmp[length] = buf;
	free(old);
	return (tmp);
}

size_t			gnl(int fd, char **line)
{
	size_t	ret;
	char	buf[1];
	char	*tmp;

	if (!(tmp = (char*)malloc(sizeof(char))))
		malloc_error();
	*tmp = '\0';
	*line = tmp;
	write(1, "bash_na_bash! ", 14); // CURRENT FOLDER BEFORE IS NEEDED
	while ((ret = read(0, buf, 1) > 0))
	{
		if (buf[0] != '\n')
		{
			tmp = bufrecorder(tmp, buf[0]);
			*line = tmp;
		}
		else
			return (ret);
	}
	if (!ret)
		return (0);
	return (-1);
}