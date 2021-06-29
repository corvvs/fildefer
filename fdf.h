#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include "ff_alloc.h"
#include <stdio.h>
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

/*
 * (x,y,z): on map-system
 * (vx,vy,vz): on view-system
 */
typedef struct s_mappoint
{
	double		x;
	double		y;
	double		z;
	double		vx;
	double		vy;
	double		vz;
	uint32_t	color;
}	t_mappoint;

typedef struct s_transform
{
	double	xx;
	double	xy;
	double	xz;
	double	xt;
	double	yx;
	double	yy;
	double	yz;
	double	yt;
	double	zx;
	double	zy;
	double	zz;
	double	zt;
	double	tx;
	double	ty;
	double	tz;
	double	tt;
}	t_transform;

typedef struct s_image
{
	void			*mlx_image;
	int32_t			*addr;
	int32_t			endian;
	int32_t			bits_per_pixel;
	int32_t			size_line;
}	t_image;

typedef struct s_master
{
	void	*mlx;
	void	*window;

	unsigned int	window_width;
	unsigned int	window_height;
	unsigned int	map_width;
	unsigned int	map_height;
	unsigned int	points_used;
	unsigned int	points_cap;
	t_ff_block		*temp_blocks;
	t_mappoint		**points;
	double			vxmin;
	double			vxmax;
	double			vymin;
	double			vymax;
	double			vzmin;
	double			vzmax;
	t_transform		transform;
	t_image			image;
}	t_master;

void	error_exit(t_master *master, char *message);
int		ff_atoi_d(char *str, int *d);
int		ff_atoi_hd(char *str, uint32_t *hd);
char	**ff_destructive_split(char *str, char c);
void	ff_read_map(t_master *master, const char *path);
void	ff_start_loop(t_master *master);

void	ff_default_transform(t_master *master);
void	ff_new_image(t_master *master);
void    ff_paint_image(t_master *master);
void	ff_apply_transform(t_master *master);
void	ff_set_tr_isometric(t_transform *t);
void	ff_tr_compose(t_transform *t, t_transform *s, t_transform *r);
void	ff_transform_point(t_transform *transform, t_mappoint *point);

void	ff_print_map(t_master *master);

#endif
