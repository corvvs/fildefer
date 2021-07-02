#include "fdf.h"

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

// calculate bounding-box
void	ff_derive_bbox(t_master *master)
{
	int			i;

	master->vxmin = +INFINITY;
	master->vymin = +INFINITY;
	master->vzmin = +INFINITY;
	master->vxmax = -INFINITY;
	master->vymax = -INFINITY;
	master->vzmax = -INFINITY;
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
