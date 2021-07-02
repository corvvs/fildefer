#include "fdf.h"

void	ff_print_map(t_master *master)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	o;

	i = -1;
	while (++i < master->map_height)
	{
		j = -1;
		while (++j < master->map_width)
			o = i * master->map_width + j;
	}
}
