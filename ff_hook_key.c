#include "fdf.h"

int	hook_key_press(int key, t_master *m)
{
	printf("key = %d\n", key);
	if (key == KEY_ESC || key == KEY_Q)
		normal_exit(m);
	if (key == KEY_0)
	{
		m->phi = 0;
		ff_set_tr_rotate(&m->tr_camera, 0);
		ff_setup_tr_project(m);
		m->tr_changed = 1;
		return (0);
	}
	if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		if (key == KEY_LEFT)
			m->phi += M_PI / 64;
		else
			m->phi -= M_PI / 64;
		ff_setup_tr_mapmod(m);
		m->tr_changed = 1;
		return (0);
	}
	if (key == KEY_UP || key == KEY_DOWN)
	{
		if (key == KEY_UP)
			m->map_zscale += 0.1;
		else
			m->map_zscale -= 0.1;
		ff_setup_tr_mapmod(m);
		m->tr_changed = 1;
		return (0);
	}
	if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
	{
		if (key == KEY_W)
			ff_pan_tr_camera(m, 0, -4.0);
		if (key == KEY_S)
			ff_pan_tr_camera(m, 0, +4.0);
		if (key == KEY_A)
			ff_pan_tr_camera(m, -4.0, 0);
		if (key == KEY_D)
			ff_pan_tr_camera(m, +4.0, 0);
		m->tr_changed = 1;
		return (0);
	}
	return (0);
}
