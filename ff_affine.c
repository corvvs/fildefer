#include "fdf.h"

/*
 * set t as an translate transform
 */
void	ff_set_tr_translate(t_transform *t, double x, double y, double z)
{
	*t = (t_transform){
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1 };
}

/*
 * set t as an scaling transform
 */
void	ff_set_tr_scale(t_transform *t, double mx, double my, double mz)
{
	*t = (t_transform){
		mx, 0, 0, 0,
		0, my, 0, 0,
		0, 0, mz, 0,
		0, 0, 0, 1 };
}

/*
 * set t as a x-rotation transform
 */
void	ff_set_tr_x_rot(t_transform *t, double phi)
{
	*t = (t_transform){
		1, 0, 0, 0,
		0, +cos(phi), -sin(phi), 0,
		0, +sin(phi), +cos(phi), 0,
		0, 0, 0, 1 };
}

/*
 * set t as a z-rotation transform
 */
void	ff_set_tr_z_rot(t_transform *t, double phi)
{
	*t = (t_transform){
		+cos(phi), -sin(phi), 0, 0,
		+sin(phi), +cos(phi), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
}
