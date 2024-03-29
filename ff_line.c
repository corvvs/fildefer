#include "fdf.h"
#include <stdio.h>

// derive a color for the point between 2 given points.
static int32_t	mix_color(t_mappoint *p1, t_mappoint *p2, double ratio, int ii, const char *s)
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
		if (ratio > 1.0)
			ratio = 1.0;
		if (ratio < 0.0)
			ratio = 0.0;
		tc = ((double)c2 - (double)c1) * ratio + (double)c1 + 0.5;
		if (tc < 0) {
			printf("[%s] tc: %f, c1: %u, c2: %u, ratio: %f, ii: %d\n", s, tc, c1, c2, ratio, ii);
			if (s == "x") {
				printf("[%s] p1x: %f, p2x %f, (ii - p1->vx) = %f / (p2->vx - p1->vx) = %f\n", s, p1->vx, p2->vx, (ii - p1->vx), (p2->vx - p1->vx));
			} else {
				printf("[%s] p1y: %f, p2y %f, (ii - p1->vy) = %f / (p2->vy - p1->vy) = %f\n", s, p1->vy, p2->vy, (ii - p1->vy), (p2->vy - p1->vy));
			}
		}
		mc += ((int)tc << n);
		n += 8;
	}
	return (mc);
}

static void	ff_connect_by_x(t_master *master, t_mappoint *p1, t_mappoint *p2,
	int capi)
{
	int			xi;
	int			yi;
	int			k;
	double		z;
	double		m;

	xi = (int)(p1->vx + 0.5);
	if (p2->vx == p1->vx)
		return ;
	m = (p2->vy - p1->vy) / (p2->vx - p1->vx);
	while (xi <= capi)
	{
		yi = (int)(m * (xi - p1->vx) + p1->vy + 0.5);
		z = (p2->vz - p1->vz) / (p2->vx - p1->vx) * (xi - p1->vx) + p1->vz;
		k = yi * master->image->size_line / sizeof(uint32_t) + xi;
		if (!ff_pixel_is_out(master, xi, yi) && master->z_buffer[k] < z)
		{
			master->z_buffer[k] = z;
			master->image->addr[k]
				= mix_color(p1, p2, (xi - p1->vx) / (p2->vx - p1->vx), xi, "x");
		}
		xi += 1;
	}
}

static void	ff_connect_by_y(t_master *master, t_mappoint *p1, t_mappoint *p2,
	int capi)
{
	int			xi;
	int			yi;
	int			k;
	double		z;
	double		m;

	yi = (int)(p1->vy + 0.5);
	if (p2->vy == p1->vy)
		return ;
	m = (p2->vx - p1->vx) / (p2->vy - p1->vy);
	while (yi <= capi)
	{
		xi = (int)(m * (yi - p1->vy) + p1->vx + 0.5);
		z = (p2->vz - p1->vz) / (p2->vy - p1->vy) * (yi - p1->vy) + p1->vz;
		k = yi * master->image->size_line / sizeof(uint32_t) + xi;
		if (!ff_pixel_is_out(master, xi, yi) && master->z_buffer[k] < z)
		{
			master->z_buffer[k] = z;
			master->image->addr[k]
				= mix_color(p1, p2, (yi - p1->vy) / (p2->vy - p1->vy), yi, "y");
		}
		yi += 1;
	}
}

void	ff_connect_points(t_master *master, int i, int j)
{
	t_mappoint	*p1;
	t_mappoint	*p2;

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
		ff_connect_by_x(master, p1, p2, (int)(p2->vx + 0.5));
	}
	else
	{
		if (p1->vy > p2->vy)
		{
			p1 = master->points[j];
			p2 = master->points[i];
		}
		ff_connect_by_y(master, p1, p2, (int)(p2->vy + 0.5));
	}
}
