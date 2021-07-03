#include "get_next_line.h"

void	get_next_line_destroy(t_tank *top)
{
	t_tank	*tmp;

	while (top)
	{
		tmp = top->next;
		if (top->buff)
			free(top->buff);
		free(top);
		top = tmp;
	}
}
