#include "fdf.h"

static int	push_point(t_master *master, t_mappoint *point)
{
	t_mappoint	**extended;

	if (master->points_used >= master->points_cap)
	{
		master->points_cap = master->points_cap * 2;
		extended = (t_mappoint **)malloc(
				master->points_cap * sizeof(t_mappoint *));
		if (!extended)
			return (-1);
		ft_memcpy(extended, master->points,
			sizeof(t_mappoint *) * master->points_used);
		free(master->points);
		master->points = extended;
	}
	master->points[master->points_used++] = point;
	return (0);
}

static size_t	array_len(char **strarray)
{
	size_t	n;

	n = 0;
	while (*(strarray++))
		n += 1;
	return (n);
}

static t_mappoint	*make_point(char *element)
{
	char			**tokens;
	size_t			token_size;
	int				z;
	unsigned int	color;
	t_mappoint		*point;

	tokens = ff_split(element, ',');
	if (!tokens)
		return (NULL);
	token_size = array_len(tokens);
	if (1 <= token_size && token_size <= 2)
	{
		if (ff_atoi_d(tokens[0], &z) == -1)
			return (NULL);
		color = 0xffffff;
		if (2 <= token_size && ff_atoi_hd(tokens[1], &color) == -1)
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

static int	convert_points(t_master *master, ssize_t row_size, char **splitted)
{
	int			err;
	ssize_t		j;
	t_mappoint	*point;

	j = -1;
	err = -1;
	while (++j < row_size)
	{
		err = -1;
		point = make_point(*(splitted + j));
		if (!point || push_point(master, point))
		{
			free(point);
			break ;
		}
		err = 0;
	}
	return (err);
}

// convert a string(line) to map points
int	ff_line_to_points(t_master *master, char *line, int status)
{
	int			err;
	ssize_t		row_size;
	char		**splitted;

	splitted = ff_split(line, ' ');
	if (!splitted)
		return (-1);
	row_size = array_len(splitted);
	if (status == 0 && row_size == 0)
	{
		free(splitted);
		return (status);
	}
	err = convert_points(master, row_size, splitted);
	free(splitted);
	if (err)
		return (err);
	if (master->map_width > 0 && master->map_width != row_size)
		return (-1);
	master->map_width = row_size;
	return (status);
}
