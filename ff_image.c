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
	ff_tr_compose(&master->tr_camera, &master->transform, &master->transform);
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

static void ff_connect_points(t_master *master, int i, int j)
{
	t_mappoint  *p1;
	t_mappoint  *p2;
	int ti;
	int ti2;
	int ui;

	p1 = master->points[i];
	p2 = master->points[j];
	// printf("(%d-%d) | (%.2f, %.2f, %.2f) -> (%.2f, %.2f, %.2f)\n", i, j, p1->vx, p1->vy, p1->vz, p2->vx, p2->vy, p2->vz);
	if (fabs(p1->vx - p2->vx) >= fabs(p1->vy - p2->vy))
	{
		if (p1->vx > p2->vx)
		{
			p1 = master->points[j];
			p2 = master->points[i];
		}
		ti = (int)(p1->vx + 0.5);
		ti2 = (int)(p2->vx + 0.5);
		while (ti <= ti2)
		{
			ui = (int)((p2->vy - p1->vy) / (p2->vx - p1->vx + 1e-10) * (ti - p1->vx) + p1->vy + 0.5);
			// printf("(%d, %d)\n", ti, ui);
			if (0 <= ti && ti < (int)master->window_width && 0 <= ui && ui < (int)master->window_height)
				master->image.addr[ui * master->image.size_line / sizeof(uint32_t) + ti] = mixed_color(p1, p2, (ti - p1->vx) / (p2->vx - p1->vx + 1e-10));
			ti += 1;
		}
	} else {
		if (p1->vy > p2->vy)
		{
			p1 = master->points[j];
			p2 = master->points[i];
		}
		ti = (int)(p1->vy + 0.5);
		ti2 = (int)(p2->vy + 0.5);
		while (ti <= ti2)
		{
			ui = (int)((p2->vx - p1->vx) / (p2->vy - p1->vy) * (ti - p1->vy) + p1->vx + 0.5);
			// printf("(%d, %d)\n", ui, ti);
			if (0 <= ui && ui < (int)master->window_width && 0 <= ti && ti < (int)master->window_height)
				master->image.addr[ti * master->image.size_line / sizeof(uint32_t) + ui] = mixed_color(p1, p2, (ti - p1->vy) / (p2->vy - p1->vy + 1e-10));
			ti += 1;
		}
	}
}

void	ff_paint_image(t_master *master)
{
	unsigned int	xy;

	ft_bzero(master->image.addr,
		(master->window_height * master->image.size_line));
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
	printf("bpp: %d, endian: %d, size_line: %d\n", m->image.bits_per_pixel, m->image.endian, m->image.size_line);
}
