#include "fdf.h"

int		push_point(t_master *master, t_mappoint *point)
{
	t_mappoint	**extended;

	if (master->points_used >= master->points_cap)
	{
		master->points_cap = master->points_cap * 2;
		extended = (t_mappoint **)malloc(master->points_cap * sizeof(t_mappoint *));
		if (!extended)
			return (-1);
		ft_memcpy(extended, master->points, sizeof(t_mappoint *) * master->points_used);
		free(master->points);
		master->points = extended;
	}
	master->points[master->points_used++] = point;
	return (0);
}

size_t	ff_arraylen(char **strarray)
{
	size_t	n;

	n = 0;
	while (*(strarray++))
		n += 1;
	return (n);
}

t_mappoint	*make_point(char *element)
{
	char			**tokens;
	size_t			token_size;
	int				z;
	unsigned int	color;
	t_mappoint		*point;

	tokens = ff_destructive_split(element, ',');
	if (!tokens)
		return (NULL);
	token_size = ff_arraylen(tokens);
	if (1 <= token_size && token_size <= 2)
	{
		if (ff_atoi_d(tokens[0], &z) == -1)
			return (NULL);
		color = 0xffffff;
		if (2 <= token_size
			&& ff_atoi_hd(tokens[1], &color) == -1)
			return (NULL);
	}
	free(tokens);
	point = (t_mappoint *)malloc(sizeof(t_mappoint));
	if (!point)
		return (NULL);
	point->z = z;
	point->color = color;
	return (point);
}

int	ff_convert_points(t_master *master, char *line, int status)
{
	int			err;
	ssize_t		j;
	ssize_t		row_size;
	char 		**splitted;
	t_mappoint	*point;

	splitted = ff_destructive_split(line, ' ');
	if (!splitted)
		return (-1);
	row_size = ff_arraylen(splitted);
	if (status == 0 && row_size == 0)
	{
		free(splitted);
		return (status);
	}
	j = -1;
	err = -1;
	while (++j < row_size)
	{
		// dprintf(STDERR_FILENO, "j: %zd |%s|\n", j, *(splitted + j));
		err = -1;
		point = make_point(*(splitted + j));
		if (!point || push_point(master, point))
		{
			free(point);
			break ;
		}
		err = 0;
	}
	free(splitted);
	if (err)
		return (err);
	// dprintf(STDERR_FILENO, "status: %d, row_size: %zd\n", status, row_size);
	if (master->map_width > 0 && master->map_width != row_size)
		return (-1);
	master->map_width = row_size;
	return (status);
}

void	ff_set_xy(t_master *master)
{
	unsigned int	i;

	i = 0;
	while (i < master->points_used)
	{
		master->points[i]->x = i % master->map_width;
		master->points[i]->y = master->map_height - i / master->map_width - 1;
		i += 1;
	}
}

void	ff_read_map(t_master *master, const char *path)
{
	int 	fd;
	int		status;
	char	*line;

	fd = open(path, O_RDONLY);
	if (!fd)
		error_exit(master, "failed to open map file");
	status = 1;
	while (status == 1)
	{
		status = get_next_line(fd, &line);
		if (status == -1)
			error_exit(master, "failed to read map file");
		status = ff_convert_points(master, line, status);
		free(line);
		if (status == -1)
			error_exit(master, "failed to convert");
	}
	if (master->points_used % master->map_width != 0)
		dprintf(STDERR_FILENO, "points vs width not matched: (%u, %u)\n", master->points_used, master->map_width);
	master->map_height = master->points_used / master->map_width;
	ff_set_xy(master);
	dprintf(STDERR_FILENO, "(%u, %u)\n", master->map_width, master->map_height);
}
