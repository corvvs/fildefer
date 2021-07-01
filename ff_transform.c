#include "fdf.h"

// make transform t as an isometric projection (for my standard)
void	ff_set_tr_isometric(t_transform *t)
{
	*t = (t_transform){
		+1 / sqrt(2), -1 / sqrt(2), 0, 0,
		+1 / sqrt(6), +1 / sqrt(6), +2 / sqrt(6), 0,
		-1 / sqrt(3), -1 / sqrt(3), +1 / sqrt(3), 0,
		0, 0, 0, 1 };
}

// make transform t as (one of) miliraty-projection.
void	ff_set_tr_military(t_transform *t)
{
	double	r;

	r = 1;
	*t = (t_transform){
		+1 / sqrt(2), -1 / sqrt(2), 0, 0,
		+1 / sqrt(2), +1 / sqrt(2), r, 0,
		-r / sqrt(2), -r / sqrt(2), 1, 0,
		0, 0, 0, 1 };
}

// make transform t as cavalier-like projection.
// (give r = 1 for cavalier, r = 0.5 for cabinet.)
void	ff_set_tr_cavalier(t_transform *t, double r)
{
	double	d;

	d = r / sqrt(2);
	*t = (t_transform){
		1, -d, 0, 0,
		0, d, 1, 0,
		d - 1, -1, d, 0,
		0, 0, 0, 1 };
}

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

/*
 * copy s into t
 */
void	ff_tr_copy(t_transform *t, t_transform *s)
{
	ft_memcpy(t, s, sizeof(t_transform));
}

/*
 * compose transforms t and s, and set the result to r.
 */
void	ff_tr_compose(t_transform *t, t_transform *s, t_transform *r)
{
	*r = (t_transform){
		t->xx * s->xx + t->xy * s->yx + t->xz * s->zx + t->xt * s->tx,
		t->xx * s->xy + t->xy * s->yy + t->xz * s->zy + t->xt * s->ty,
		t->xx * s->xz + t->xy * s->yz + t->xz * s->zz + t->xt * s->tz,
		t->xx * s->xt + t->xy * s->yt + t->xz * s->zt + t->xt * s->tt,
		t->yx * s->xx + t->yy * s->yx + t->yz * s->zx + t->yt * s->tx,
		t->yx * s->xy + t->yy * s->yy + t->yz * s->zy + t->yt * s->ty,
		t->yx * s->xz + t->yy * s->yz + t->yz * s->zz + t->yt * s->tz,
		t->yx * s->xt + t->yy * s->yt + t->yz * s->zt + t->yt * s->tt,
		t->zx * s->xx + t->zy * s->yx + t->zz * s->zx + t->zt * s->tx,
		t->zx * s->xy + t->zy * s->yy + t->zz * s->zy + t->zt * s->ty,
		t->zx * s->xz + t->zy * s->yz + t->zz * s->zz + t->zt * s->tz,
		t->zx * s->xt + t->zy * s->yt + t->zz * s->zt + t->zt * s->tt,
		t->tx * s->xx + t->ty * s->yx + t->tz * s->zx + t->tt * s->tx,
		t->tx * s->xy + t->ty * s->yy + t->tz * s->zy + t->tt * s->ty,
		t->tx * s->xz + t->ty * s->yz + t->tz * s->zz + t->tt * s->tz,
		t->tx * s->xt + t->ty * s->yt + t->tz * s->zt + t->tt * s->tt
	};
}

void	ff_transform_point(t_transform *transform, t_mappoint *point)
{
	t_transform	*f;
	t_mappoint	*p;

	f = transform;
	p = point;
	p->vx = f->xx * p->x + f->xy * p->y + f->xz * p->z + f->xt;
	p->vy = f->yx * p->x + f->yy * p->y + f->yz * p->z + f->yt;
	p->vz = f->zx * p->x + f->zy * p->y + f->zz * p->z + f->zt;
}

// calculate bounding-box
void	ff_derive_bbox(t_master *master)
{
	int			i;

	master->vxmin = +1E300;
	master->vymin = +1E300;
	master->vzmin = +1E300;
	master->vxmax = -1E300;
	master->vymax = -1E300;
	master->vzmax = -1E300;
	i = -1;
	while (++i < (int)master->points_used)
	{
		if (master->vxmin > master->points[i]->vx)
			master->vxmin = master->points[i]->vx;
		if (master->vxmax < master->points[i]->vx)
			master->vxmax = master->points[i]->vx;
		if (master->vymin > master->points[i]->vy)
			master->vymin = master->points[i]->vy;
		if (master->vymax < master->points[i]->vy)
			master->vymax = master->points[i]->vy;
		if (master->vzmin > master->points[i]->vz)
			master->vzmin = master->points[i]->vz;
		if (master->vzmax < master->points[i]->vz)
			master->vzmax = master->points[i]->vz;
	}
}

void	ff_setup_tr_mapmod(t_master *m)
{
	t_transform	t;

	ff_set_tr_scale(&m->tr_mapmod, 1, 1, m->map_zscale);
	ff_set_tr_z_rot(&t, m->phi);
	ff_tr_compose(&t, &m->tr_mapmod, &m->tr_mapmod);
	ff_set_tr_x_rot(&t, m->theta);
	ff_tr_compose(&t, &m->tr_mapmod, &m->tr_mapmod);
}

void	ff_setup_tr_project(t_master *m)
{
	t_transform	t;
	double		mag;

	ff_setup_tr_mapmod(m);
	ff_tr_compose(&m->tr_project, &m->tr_mapmod, &m->transform);
	ff_apply_transform(m);
	ff_derive_bbox(m);
	ff_set_tr_translate(&m->tr_framing,
		-(m->vxmin + m->vxmax) / 2, -(m->vymin + m->vymax) / 2, 0);
	ff_set_tr_translate(&t, -m->window_width / 2., -m->window_height / 2., 0);
	if (m->vxmax != m->vxmin && m->vymax != m->vymin)
	{
		mag = m->window_width / (m->vxmax - m->vxmin);
		if (mag > m->window_height / (m->vymax - m->vymin))
			mag = m->window_height / (m->vymax - m->vymin);
		ff_set_tr_scale(&t, mag, mag, mag);
		ff_tr_compose(&t, &(m->tr_framing), &(m->tr_framing));
	}
	ff_set_tr_translate(&t, m->window_width / 2., m->window_height / 2., 0);
	ff_tr_compose(&t, &(m->tr_framing), &(m->tr_framing));
	ff_set_tr_scale(&t, 1, -1, 1);
	ff_tr_compose(&t, &(m->tr_framing), &(m->tr_framing));
	ff_set_tr_translate(&t, 0, 1 * m->window_height, 0);
	ff_tr_compose(&t, &(m->tr_framing), &(m->tr_framing));
	ff_set_tr_z_rot(&m->tr_camera, 0);
}

void	ff_pan_tr_camera(t_master *master, double dx, double dy)
{
	t_transform	t;

	ff_set_tr_translate(&t, dx, dy, 0);
	ff_tr_compose(&t, &master->tr_camera, &master->tr_camera);
}

void	ff_zoom_tr_camera(t_master *master, double cx, double cy, double m)
{
	t_transform	t;

	ff_set_tr_translate(&t, -cx, -cy, 0);
	ff_tr_compose(&t, &master->tr_camera, &master->tr_camera);
	ff_set_tr_scale(&t, m, m, m);
	ff_tr_compose(&t, &master->tr_camera, &master->tr_camera);
	ff_set_tr_translate(&t, cx, cy, 0);
	ff_tr_compose(&t, &master->tr_camera, &master->tr_camera);
}
