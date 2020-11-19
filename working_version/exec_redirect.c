#include "minishell.h"

int     **dir_exec(int **fd, char *operator, char *operand)
{
    //printf("operand is %s\n", operand);
    if (**fd && *operator == 0x3c)
        close(**fd);
    else if (*(*fd + 1) != 1 && *operator == 0x3e)
        close(*(*fd + 1));
    if (*operator == 0x3c)
	{
		if ((**fd = open(operand, O_RDONLY)) == -1)
			{
				**fd = 0;
				write(1, "No such file or directory", 25); // нужен ошибка и minishell()
			}
	}
    else if (!ft_memcmp(">", operator, 2))
    {
    	//printf("operator detected\n");
		*(*fd + 1) = open(operand, O_RDWR | O_CREAT, S_IRWXU);
    }
    else
	{
        //printf("wrong operator detected\n");
		*(*fd + 1) = open(operand, O_RDWR | O_CREAT| O_APPEND, S_IRWXU);
	}
   	//printf("opened descriptor is %i\n", *(*fd + 1));
	return (fd);
}