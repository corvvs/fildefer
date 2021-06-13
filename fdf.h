#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include "ff_alloc.h"
#include <stdio.h>

typedef struct s_mappoint
{
	int			x;
	int			y;
	int			z;
	uint32_t	color;
}	t_mappoint;

typedef struct s_master
{
	void	*mlx;
	void	*window;

	unsigned int	map_width;
	unsigned int	map_height;
	unsigned int	points_used;
	unsigned int	points_cap;
	t_ff_block		*temp_blocks;
	t_mappoint		**points;
}	t_master;

void	error_exit(t_master *master, char *message);
int		ff_atoi_d(char *str, int *d);
int		ff_atoi_hd(char *str, uint32_t *hd);
char	**ff_destructive_split(char *str, char c);
void	ff_read_map(t_master *master, const char *path);

#endif
