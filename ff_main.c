#include "fdf.h"

static t_master	*init_master(void)
{
	t_master	*master;

	master = (t_master *)ft_calloc(1, sizeof(t_master));
	if (!master)
		error_exit(master, "failed to alloc master");
	master->window_width = WIN_WIDTH;
	master->window_height = WIN_HEIGHT;
	master->points_cap = 32;
	master->points = (t_mappoint **)malloc(
			master->points_cap * sizeof(t_mappoint *));
	if (!(master->points))
		error_exit(master, "failed to alloc points");
	master->map_zscale = 1;
	ff_set_tr_isometric(&master->tr_project);
	return (master);
}

static void	init_mlx(t_master *master)
{
	master->mlx = mlx_init();
	if (!(master->mlx))
		error_exit(master, "failed to new mlx");
	master->window = mlx_new_window(master->mlx,
			master->window_width, master->window_height,
			(char *)master->file_name);
	if (!(master->window))
		error_exit(master, "failed to new window");
}

int	main(int argc, char **argv)
{
	t_master	*master;

	if (argc != 2)
		error_exit(NULL, "usage: ./fdf [map file path]");
	master = init_master();
	ff_read_map(master, argv[1]);
	init_mlx(master);
	ff_start_loop(master);
	normal_exit(master);
	return (0);
}
