#include "fdf.h"


void	ff_print_map(t_master *master)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	o;

	dprintf(STDERR_FILENO, "width: %u height: %u\n", master->map_width, master->map_height);
	i = -1;
	while (++i < master->map_height)
	{
		j = -1;
		while(++j < master->map_width)
		{
			o = i * master->map_width + j;
			dprintf(STDERR_FILENO, "%f:%#06x%*s", master->points[o]->z, master->points[o]->color, j < master->map_width - 1, " ");
		}
		dprintf(STDERR_FILENO, "\n");
	}
}