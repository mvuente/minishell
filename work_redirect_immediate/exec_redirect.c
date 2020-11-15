#include "minishell.h"

int     **dir_exec(int **fd, char *operator, char *operand)
{
    printf("operand is %s\n", operand);
    if (**fd && *operator == 0x3c)
        close(**fd);
    else if (*(*fd + 1) != 1 && *operator == 0x3e)
        close(*(*fd+ 1));
    if (*operator == 0x3c)
        **fd = open(operand, O_RDONLY);
    else if (!ft_memcmp(">", operator, 2))
        *(*fd + 1) = open(operand, O_RDWR | O_CREAT);
    else
        *(*fd + 1) = open(operand, O_RDWR | O_CREAT| O_APPEND);
    return (fd);
}