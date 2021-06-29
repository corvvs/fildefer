#include "fdf.h"

void	destroy_master(t_master *master)
{
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
	if (master->temp_blocks)
	{
		ff_free(master->temp_blocks);
		free(master->temp_blocks);
		master->temp_blocks = NULL;
	}
	if (master->points)
	{
		unsigned int i = -1;
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

t_master	*init_master(void)
{
	t_master	*master;

	master = (t_master *)ft_calloc(1, sizeof(t_master));
	if (!master)
		error_exit(master, "failed to alloc master");
	master->temp_blocks = ff_new_block_list(NULL);
	if (!(master->temp_blocks))
		error_exit(master, "failed to alloc temp_blocks");
	master->mlx = mlx_init();
	if (!(master->mlx))
		error_exit(master, "failed to new mlx");
	master->window_width = WIN_WIDTH;
	master->window_height = WIN_HEIGHT;
	master->window = mlx_new_window(master->mlx, master->window_width, master->window_height, "fir de fer");
	if (!(master->window))
		error_exit(master, "failed to new window");
	master->points_cap = 32;
	master->points = (t_mappoint **)malloc(master->points_cap * sizeof(t_mappoint *));
	ff_set_tr_isometric(&master->transform);
	ff_set_tr_isometric(&master->tr_stage);
	ff_set_tr_rotate(&master->tr_rot, master->phi);
	ff_set_tr_rotate(&master->tr_camera, 0);
	master->camera_zoom = 1;
	return (master);
}

int main(int argc, char **argv)
{
	t_master	*master;

	if (argc != 2)
		error_exit(NULL, "usage: ./fdf [map file path]");
	setvbuf(stdout, (char *)NULL, _IONBF, 0);
	master = init_master();
	ff_read_map(master, argv[1]);
	// mlx_string_put(master->mlx, master->window, 100, 100, 0xffffff, "Hello World");
	ff_start_loop(master);
	ff_print_map(master);
	destroy_master(master);
	// system("leaks fdf");
	return (0);
}
