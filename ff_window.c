#include "fdf.h"

int	ff_main_loop(t_master *master)
{
	(void)master;
	// ff_apply_transform(master);
	// mlx_put_image_to_window(master->->mlx, master->window, w->img.img, 0, 0);
	return (0);
}

void	ff_start_loop(t_master *master)
{
	ff_new_image(master);
	ff_default_transform(master);
	ff_apply_transform(master);
	ff_paint_image(master);
	mlx_loop_hook(master->mlx, &ff_main_loop, master);
	mlx_loop(master->mlx);
}
