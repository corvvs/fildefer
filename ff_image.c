#include "fdf.h"

static void	ff_transform_point(t_transform *transform, t_mappoint *point)
{
	t_transform	*f;
	t_mappoint	*p;

	f = transform;
	p = point;
	p->vx = f->xx * p->x + f->xy * p->y + f->xz * p->z + f->xt;
	p->vy = f->yx * p->x + f->yy * p->y + f->yz * p->z + f->yt;
	p->vz = f->zx * p->x + f->zy * p->y + f->zz * p->z + f->zt;
}

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
		i += 1;
	}
}

// initialize all z_buffer cells by (nearly) -inf
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

void	ff_draw_image(t_master *master)
{
	unsigned int	xy;

	ft_bzero(master->image->addr,
		(master->window_height * master->image->size_line));
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
	mlx_put_image_to_window(master->mlx, master->window,
		master->image->mlx_image, 0, 0);
	master->ii = 1 - master->ii;
	master->image = &(master->images[master->ii]);
}

void	ff_new_image(t_master *master, int i)
{
	t_master	*m;
	t_image		*img;

	m = master;
	img = &(m->images[i]);
	img->mlx_image = mlx_new_image(m->mlx,
			m->window_width, m->window_height);
	if (!(img->mlx_image))
		error_exit(m, "failed to mlx_new_image");
	img->addr = (int32_t *)mlx_get_data_addr(
			img->mlx_image,
			&(img->bits_per_pixel),
			&(img->size_line),
			&(img->endian)
			);
	if (!(img->addr))
		error_exit(m, "failed to mlx_get_data_addr");
	m->image_size = (m->window_height * img->size_line) / sizeof(uint32_t);
}
