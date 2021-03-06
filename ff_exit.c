#include "fdf.h"

static void	destroy_images(t_master *master)
{
	if (!master)
		return ;
	if (master->images[0].mlx_image && !master->images[0].destroyed)
	{
		master->images[0].destroyed = 1;
		mlx_destroy_image(master->mlx, master->images[0].mlx_image);
	}
	if (master->images[1].mlx_image && !master->images[1].destroyed)
	{
		master->images[1].destroyed = 1;
		mlx_destroy_image(master->mlx, master->images[1].mlx_image);
	}
	if (master->z_buffer)
	{
		free(master->z_buffer);
		master->z_buffer = NULL;
	}
}

#ifdef MLX_MMS
static void	destroy_master(t_master *master)
{
	unsigned int	i;

	if (!master)
		return ;
	if (master->mlx)
	{
		destroy_images(master);
		if (master->window && !master->destroying_window)
		{
			master->destroying_window = 1;
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

#else

static void	destroy_master(t_master *master)
{
	unsigned int	i;

	if (!master)
		return ;
	if (master->mlx)
	{
		destroy_images(master);
		if (master->window)
		{
			mlx_destroy_window(master->mlx, master->window);
			master->window = NULL;
		}
		mlx_destroy_display(master->mlx);
		free(master->mlx);
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
	get_next_line(0, NULL, 1);
}
#endif

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
