#include "minishell.h"

void	read_error(void)
{
	write(2, "An error while reading the line\n", 32);
	exit(1);
}

void	malloc_error(void)
{
	write(2, "An error while memory allocating\n", 33);
	exit(1);
}

void	command_error(void)
{
	write(2, "wrong command\n", 14);
	exit(1);
}

void	some_error(void)
{
	write(2, "something wrong\n", 16);
	exit(1);
}

int		delim_error(char *delim, int flag)
{
	errno = 258;
	write(2, "e-bash: ", 8);
	write(2, "syntax error near unexpected token", 34);
	write(2, "`", 1);
	write(2, delim, 1);
	if (flag == 2)
		write(2, delim, 1);
	write(2, "\'", 1);
	write(2, "\n", 1);
	return (1);
}
