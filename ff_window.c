#include "fdf.h"

int	ff_main_loop(t_master *master)
{
	if (master->painting || !master->tr_changed)
		return (0);
	master->painting = 1;
	ff_tr_compose(&master->tr_project, &master->tr_mapmod, &master->transform);
	ff_tr_compose(&master->tr_framing, &master->transform, &master->transform);
	ff_tr_compose(&master->tr_camera, &master->transform, &master->transform);
	ff_apply_transform(master);
	ff_draw_image(master);
	master->painting = 0;
	master->tr_changed = 0;
	return (0);
}

void	ff_start_loop(t_master *master)
{
	ff_new_image(master, 0);
	ff_new_image(master, 1);
	master->z_buffer
		= (double *)malloc(master->image_size * sizeof(double));
	if (!(master->z_buffer))
		error_exit(master, "failed to alloc z_buffer");
	master->image = &(master->images[master->ii]);
	ff_setup_tr_project(master);
	master->tr_changed = 1;
	mlx_loop_hook(master->mlx, &ff_main_loop, master);
	mlx_hook(master->window, EVENT_KEY_PRESS,
		MASK_KEY_PRESS, &hook_key_press, master);
	mlx_hook(master->window, EVENT_MOUSE_PRESS,
		MASK_MOUSE_PRESS, &hook_mouse_down, master);
	mlx_hook(master->window, EVENT_MOUSE_RELEASE,
		MASK_MOUSE_RELEASE, &hook_mouse_up, master);
	mlx_hook(master->window, EVENT_MOTION,
		MASK_MOTION, &hook_motion, master);
	mlx_loop(master->mlx);
}
