#include "fdf.h"

// move camera with displacement (dx, dy) on C-system
void	ff_pan_camera(t_master *master, double dx, double dy)
{
	t_transform	t;

	ff_set_tr_translate(&t, dx, dy, 0);
	ff_tr_compose(&t, &master->tr_camera, &master->tr_camera);
}

// zoom by a magnitude m, centered at (cx, cy) on C-system
void	ff_zoom_camera(t_master *master, double cx, double cy, double m)
{
	t_transform	t;

	ff_set_tr_translate(&t, -cx, -cy, 0);
	ff_tr_compose(&t, &master->tr_camera, &master->tr_camera);
	ff_set_tr_scale(&t, m, m, m);
	ff_tr_compose(&t, &master->tr_camera, &master->tr_camera);
	ff_set_tr_translate(&t, cx, cy, 0);
	ff_tr_compose(&t, &master->tr_camera, &master->tr_camera);
}
