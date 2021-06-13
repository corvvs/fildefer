#ifndef FF_ALLOC_H
# define FF_ALLOC_H

# include <stdlib.h>
# include <limits.h>
# include "libft.h"

typedef struct s_ff_block
{
	void				*block;
	size_t				size;
	struct s_ff_block	*prev;
	struct s_ff_block	*next;
}	t_ff_block;

t_ff_block	*ff_push_block(t_ff_block *sentinel, void *block);
t_ff_block	*ff_new_block_list(void *block);
void		*ff_malloc(t_ff_block *sentinel, size_t	n);
size_t		ff_free(t_ff_block *sentinel);
void		ff_free_strs(char **strs);
t_ff_block	*ff_push_strs(t_ff_block *sentinel, char **strs);

#endif