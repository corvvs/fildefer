#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdint.h>
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include "ff_alloc.h"
# ifdef MLX_MMS
#  include "ff_key.h"
# else
#  include "ff_key_linux.h"
# endif
#include <stdio.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define EVENT_KEY_PRESS 2
# define EVENT_MOUSE_PRESS 4
# define EVENT_MOUSE_RELEASE 5
# define EVENT_MOTION 6
# define MASK_KEY_PRESS 1L
# define MASK_MOUSE_PRESS 4L
# define MASK_MOUSE_RELEASE 8L
# define MASK_MOTION 64L

typedef struct s_vector
{
	double		x;
	double		y;
	double		z;
}	t_vector;

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
	void			*mlx;
	void			*window;
	const char		*file_name;

	unsigned int	window_width;
	unsigned int	window_height;
	unsigned int	map_width;
	unsigned int	map_height;
	unsigned int	points_used;
	unsigned int	points_cap;
	t_mappoint		**points;
	double			vxmin;
	double			vxmax;
	double			vymin;
	double			vymax;
	double			vzmin;
	double			vzmax;
	t_transform		tr_project;
	t_transform		tr_mapmod;
	t_transform		tr_framing;
	t_transform		tr_camera;
	t_transform		transform;
	double			phi;
	double			theta;
	double			map_zscale;
	int				ii;
	t_image			images[2];
	t_image			*image;
	size_t			image_size;
	double			*z_buffer;
	int				painting;
	int				tr_changed;
	int				dragging;
	int				do_x;
	int				do_y;
}	t_master;

void	error_exit(t_master *master, char *message);
void	normal_exit(t_master *master);
int		ff_atoi_d(char *str, int *d);
int		ff_atoi_hd(char *str, uint32_t *hd);
char	**ff_destructive_split(char *str, char c);
int		ff_line_to_points(t_master *master, char *line, int status);
void	ff_read_map(t_master *master, const char *path);
void	ff_start_loop(t_master *master);

void	ff_setup_tr_mapmod(t_master *master);
void	ff_setup_tr_project(t_master *master);
void	ff_pan_tr_camera(t_master *master, double dx, double dy);
void	ff_zoom_tr_camera(t_master *master, double cx, double cy, double m);
void	ff_new_image(t_master *master, int i);
void	ff_draw_image(t_master *master);
void	ff_apply_transform(t_master *master);
void	ff_set_tr_isometric(t_transform *t);
void	ff_set_tr_military(t_transform *t);
void	ff_set_tr_cavalier(t_transform *t, double r);
void	ff_set_tr_translate(t_transform *t, double x, double y, double z);
void	ff_set_tr_scale(t_transform *t, double mx, double my, double mz);
void	ff_set_tr_x_rot(t_transform *t, double phi);
void	ff_set_tr_z_rot(t_transform *t, double phi);
void	ff_form_transform(t_master *master);
void	ff_tr_compose(t_transform *t, t_transform *s, t_transform *r);
int		ff_pixel_is_out(t_master *master, int x, int y);
int		ff_point_is_out(t_master *master, t_mappoint *p);
int		ff_segment_is_crossing(t_mappoint *p1, t_mappoint *p2,
			t_vector *q1, t_vector *q2);
int		ff_segment_is_out(t_master *master, t_mappoint *p1, t_mappoint *p2);
void	ff_connect_points(t_master *master, int i, int j);

int		hook_key_press(int key, t_master *master);
int		hook_mouse_down(int button, int x, int y, t_master *master);
int		hook_mouse_up(int button, int x, int y, t_master *master);
int		hook_motion(int x, int y, t_master *master);

#endif
