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
