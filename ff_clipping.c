#include "fdf.h"

// returns 1, if a given pixel is out of the screen
int	ff_pixel_is_out(t_master *master, int x, int y)
{
	return (x < 0 || (int)master->window_width <= x
		|| y < 0 || (int)master->window_height <= y);
}

// returns 1, if a given point is out of the screen
int	ff_point_is_out(t_master *master, t_mappoint *p)
{
	return (p->vx < 0 || master->window_width <= p->vx
		|| p->vy < 0 || master->window_height <= p->vy);
}

int	ff_segment_is_crossing(t_mappoint *p1, t_mappoint *p2,
	t_vector *q1, t_vector *q2)
{
	double	denom;
	double	s;

	denom = (p2->vx - p1->vx) * (q2->y - q1->y)
		- (p2->vy - p1->vy) * (q2->x - q1->x);
	if (denom == 0)
		return (0);
	s = ((q2->y - q1->y) * (q1->x - p1->vx)
			- (q2->x - q1->x) * (q1->y - p1->vy)) / denom;
	if (s < 0 || 1 < s)
		return (0);
	s = ((p2->vy - p1->vy) * (q1->x - p1->vx)
			- (p2->vx - p1->vx) * (q1->y - p1->vy)) / denom;
	if (s < 0 || 1 < s)
		return (0);
	return (1);
}

// returns 1, if a segment formed by 2 given points
// is entirely out of the screen.
int	ff_segment_is_out(t_master *master, t_mappoint *p1, t_mappoint *p2)
{
	t_vector	q1;
	t_vector	q2;

	if (!ff_point_is_out(master, p1) || !ff_point_is_out(master, p2))
		return (0);
	q1 = (t_vector){0, 0, 0};
	q2 = (t_vector){master->window_width, 0, 0};
	if (ff_segment_is_crossing(p1, p2, &q1, &q2))
		return (0);
	q1 = (t_vector){master->window_width, master->window_height, 0};
	if (ff_segment_is_crossing(p1, p2, &q2, &q1))
		return (0);
	q2 = (t_vector){0, master->window_height, 0};
	if (ff_segment_is_crossing(p1, p2, &q1, &q2))
		return (0);
	q1 = (t_vector){0, 0, 0};
	if (ff_segment_is_crossing(p1, p2, &q2, &q1))
		return (0);
	return (1);
}
