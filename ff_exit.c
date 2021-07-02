#include "fdf.h"

void	destroy_master(t_master *master)
{
	unsigned int	i;

	if (!master)
		return ;
	if (master->mlx)
	{
		if (master->window)
		{
			mlx_destroy_window(master->mlx, master->window);
			master->window = NULL;
		}
		master->mlx = NULL;
	}
	if (master->points)
	{
		i = -1;
		while (++i < master->points_used)
			free(master->points[i]);
		free(master->points);
	}
	free(master);
}

void	error_exit(t_master *master, char *message)
{
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	destroy_master(master);
	exit(1);
}

void	normal_exit(t_master *master)
{
	destroy_master(master);
	exit(0);
}
