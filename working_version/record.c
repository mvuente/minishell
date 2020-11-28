#include "minishell.h"



//t_set	wordrcrdr(char *item, t_list *word) // change return
//{
//	if (!word)
//		set.word = item;
//	else
//	{ 
//		
//		
//		
//		
//		if (!(set.word = ft_strjoin(set.word, " ")))
//			malloc_error();
//		if (!(set.word = ft_strjoin(set.word, item)))
//			malloc_error();
//	}
//	return (set);
//}

t_set	builtinrcrdr(char *item, t_set set)
{	
	if (!(set.builtin))
		set.builtin = item;
	else if (!set.word && !set.spec)
	{
		//printf("item is %s\n", item);
		if (!ft_memcmp(item, "-n", 3))
			{
				set.spec = 0x1;
				free(item);
			}
		else
			set.word = lstaddback(set.word, item);
	}
	else 
		set.word = lstaddback(set.word, item);
	return (set);
}