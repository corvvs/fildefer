#include "ff_alloc.h"

void	ff_free_strs(char **strs)
{
	while (*strs)
		free(*(strs++));
}

/*
 * push strs into list.
 * only if it fails, strs will be free-ed.
 */
t_ff_block	*ff_push_strs(t_ff_block *sentinel, char **strs)
{
	size_t	i;

	i = 0;
	while (*(strs + i))
	{
		if (!ff_push_block(sentinel, *(strs + i)))
			return (NULL);
		i += 1;
	}
	return (sentinel);
}
