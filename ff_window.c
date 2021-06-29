#include "fdf.h"

int	ff_main_loop(t_master *master)
{
	(void)master;
	if (master->painting || !master->tr_changed)
		return (0);
	master->painting = 1;
	ff_form_transform(master);
	ff_apply_transform(master);
	ff_paint_image(master);
	master->painting = 0;
	master->tr_changed = 0;
	return (0);
}

void	ff_start_loop(t_master *master)
{
	ff_new_image(master);
	ff_default_transform(master);
	mlx_loop_hook(master->mlx, &ff_main_loop, master);
	mlx_hook(master->window, EVENT_KEY_PRESS,
		MASK_KEY_PRESS, &hook_key_press, master);
	mlx_loop(master->mlx);
}
