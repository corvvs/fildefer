#include "fdf.h"

int	hook_key_press(int key, t_master *master)
{
	printf("key = %d\n", key);
	if (key == KEY_ESC)
		normal_exit(master);
	if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		if (key == KEY_LEFT)
			master->phi += M_PI / 64;
		else
			master->phi -= M_PI / 64;
		ff_set_tr_rotate(&master->tr_rot, master->phi);
		master->tr_changed = 1;
	}
	if (key == KEY_UP || key == KEY_DOWN)
	{
		if (key == KEY_UP)
			master->camera_zoom *= 1.1;
		else
			master->camera_zoom *= 0.9;
		ff_set_tr_camera(master);
		master->tr_changed = 1;
	}
	return (0);
}
