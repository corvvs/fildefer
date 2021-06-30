#include "fdf.h"

/*
 * apply current transform to all map points
 */
void	ff_apply_transform(t_master *master)
{
	unsigned int	i;

	i = 0;
	while (i < master->points_used)
	{
		ff_transform_point(&(master->transform), master->points[i]);
		// printf("[%d] (%.2f,%.2f,%.2f) -> (%.2f,%.2f,%.2f)\n",
		// 	i,
		// 	master->points[i]->x, master->points[i]->y, master->points[i]->z,
		// 	master->points[i]->vx, master->points[i]->vy, master->points[i]->vz
		// );
		i += 1;
	}
}

void	ff_form_transform(t_master *master)
{
	ff_tr_compose(&master->tr_stage, &master->tr_rot, &master->transform);
	ff_tr_compose(&master->tr_project, &master->transform, &master->transform);
	ff_tr_compose(&master->tr_camera, &master->transform, &master->transform);
	// t_transform *r = &master->tr_camera;
	// printf("%+.2f %+.2f %+.2f %+.2f\n", r->xx, r->xy, r->xz, r->xt);
	// printf("%+.2f %+.2f %+.2f %+.2f\n", r->yx, r->yy, r->yz, r->yt);
	// printf("%+.2f %+.2f %+.2f %+.2f\n", r->zx, r->zy, r->zz, r->zt);
	// printf("%+.2f %+.2f %+.2f %+.2f\n", r->tx, r->ty, r->tz, r->tt);
}

static int32_t	mixed_color(t_mappoint *p1, t_mappoint *p2, double ratio)
{
	int			n;
	uint32_t	c1;
	uint32_t	c2;
	double		tc;
	int32_t		mc;

	n = 0;
	mc = 0;
	while (n <= 16)
	{
		c1 = (p1->color >> n) & 0xff;
		c2 = (p2->color >> n) & 0xff;
		tc = ((double)c2 - (double)c1) * ratio + (double)c1 + 0.5;
		mc += ((int)tc << n);
		n += 8;
	}
	return (mc);
}

int	ff_pixel_is_clipped(t_master *master, int x, int y)
{
	return (x < 0 || (int)master->window_width <= x
		|| y < 0 || (int)master->window_height <= y);
}

int	ff_point_is_out(t_master *master, t_mappoint *p)
{
	return (p->vx < 0 || master->window_width <= p->vx
		|| p->vy < 0 || master->window_height <= p->vy);
}

int	ff_segment_is_crossing(t_mappoint *p1, t_mappoint *p2, t_vector *q1, t_vector *q2)
{
	double	denom;
	double	s;

	denom = (p2->vx - p1->vx) * (q2->y - q1->y) - (p2->vy - p1->vy) * (q2->x - q1->x);
	if (denom == 0)
		return (0);
	s = ((q2->y - q1->y) * (q1->x - p1->vx) - (q2->x - q1->x) * (q1->y - p1->vy)) / denom;
	if (s < 0 || 1 < s)
		return (0);
	s = (+(p2->vy - p1->vy) * (q1->x - p1->vx) - (p2->vx - p1->vx) * (q1->y - p1->vy)) / denom;
	if (s < 0 || 1 < s)
		return (0);
	return (1);
}

int	ff_segment_is_out(t_master *master, t_mappoint *p1, t_mappoint *p2)
{
	t_vector	q1;
	t_vector	q2;

	if (!ff_point_is_out(master, p1) || !ff_point_is_out(master, p2))
		return (0);
	q1 = (t_vector){ 0, 0, 0 };
	q2 = (t_vector){ master->window_width, 0, 0 };
	if (ff_segment_is_crossing(p1, p2, &q1, &q2))
		return (0);
	q1 = (t_vector){ master->window_width, master->window_height, 0 };
	if (ff_segment_is_crossing(p1, p2, &q2, &q1))
		return (0);
	q2 = (t_vector){ 0, master->window_height, 0 };
	if (ff_segment_is_crossing(p1, p2, &q1, &q2))
		return (0);
	q1 = (t_vector){ 0, 0, 0 };
	if (ff_segment_is_crossing(p1, p2, &q2, &q1))
		return (0);
	return (1);
}

static void ff_connect_points(t_master *master, int i, int j)
{
	t_mappoint	*p1;
	t_mappoint	*p2;
	int			xi;
	int			capi;
	int			yi;
	int			k;
	double		z;

	p1 = master->points[i];
	p2 = master->points[j];
	if (ff_segment_is_out(master, p1, p2))
		return ;
	if (fabs(p1->vx - p2->vx) >= fabs(p1->vy - p2->vy))
	{
		if (p1->vx > p2->vx)
		{
			p1 = master->points[j];
			p2 = master->points[i];
		}
		xi = (int)(p1->vx + 0.5);
		capi = (int)(p2->vx + 0.5);
		double m = (p2->vy - p1->vy) / (p2->vx - p1->vx + 1e-10);
		while (xi <= capi)
		{
			yi = (int)(m * (xi - p1->vx) + p1->vy + 0.5);
			z = (p2->vz - p1->vz) / (p2->vx - p1->vx + 1e-10) * (xi - p1->vx) + p1->vz;
			k = yi * master->image.size_line / sizeof(uint32_t) + xi;
			if (!ff_pixel_is_clipped(master, xi, yi) && master->z_buffer[k] < z)
			{
				master->z_buffer[k] = z;
				master->image.addr[k] = mixed_color(p1, p2, (xi - p1->vx) / (p2->vx - p1->vx + 1e-10));
			}
			xi += 1;
		}
	} else {
		if (p1->vy > p2->vy)
		{
			p1 = master->points[j];
			p2 = master->points[i];
		}
		yi = (int)(p1->vy + 0.5);
		capi = (int)(p2->vy + 0.5);
		double m = (p2->vx - p1->vx) / (p2->vy - p1->vy + 1e-10);
		while (yi <= capi)
		{
			xi = (int)(m * (yi - p1->vy) + p1->vx + 0.5);
			z = (p2->vz - p1->vz) / (p2->vy - p1->vy + 1e-10) * (yi - p1->vy) + p1->vz;
			k = yi * master->image.size_line / sizeof(uint32_t) + xi;
			if (!ff_pixel_is_clipped(master, xi, yi) && master->z_buffer[k] < z)
			{
				master->z_buffer[k] = z;
				master->image.addr[k] = mixed_color(p1, p2, (yi - p1->vy) / (p2->vy - p1->vy + 1e-10));
			}
			yi += 1;
		}
	}
}

void	ff_fill_zbuffer(t_master *master)
{
	size_t	i;

	i = 0;
	while (i < master->image_size)
	{
		master->z_buffer[i] = -1e300;
		i += 1;
	}
}

void	ff_paint_image(t_master *master)
{
	unsigned int	xy;

	ft_bzero(master->image.addr,
		(master->window_height * master->image.size_line));
	ff_fill_zbuffer(master);
	xy = 0;
	while (xy < master->map_height * master->map_width)
	{
		if (xy / master->map_width + 1 < master->map_height)
			ff_connect_points(master, xy, xy + master->map_width);
		if (xy % master->map_width + 1 < master->map_width)
			ff_connect_points(master, xy, xy + 1);
		xy += 1;
	}
	mlx_put_image_to_window(master->mlx, master->window, master->image.mlx_image, 0, 0);
}

void	ff_new_image(t_master *master) 
{
	t_master	*m;

	m = master;
	m->image.mlx_image = mlx_new_image(m->mlx,
		m->window_width, m->window_height);
	if (!(m->image.mlx_image))
		error_exit(m, "failed to mlx_new_image");
	m->image.addr = (int32_t *)mlx_get_data_addr(
		m->image.mlx_image,
		&(m->image.bits_per_pixel),
		&(m->image.size_line),
		&(m->image.endian)
		);
	if (!(m->image.addr))
		error_exit(m, "failed to mlx_get_data_addr");
	m->image_size = (m->window_height * m->image.size_line) / sizeof(uint32_t);
	m->z_buffer = (double *)malloc(m->image_size * sizeof(double));
	if (!(m->z_buffer))
		error_exit(m, "failed to alloc z_buffer");
}
