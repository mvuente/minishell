#include "minishell.h"

void	read_error(void)
{
	write(1, "An error while reading the line\n", 32);
	exit(1);
}

void	malloc_error(void)
{
	write(1, "An error while memory allocating\n", 33);
	exit(1);
}

