#include "fdf.h"

void	ff_set_xy(t_master *m)
{
	unsigned int	i;

	i = 0;
	while (i < m->points_used)
	{
		m->points[i]->x
			= i % m->map_width - (double)m->map_width / 2;
		m->points[i]->y
			= m->map_height - i / m->map_width - 1 - (double)m->map_height / 2;
		i += 1;
	}
}

void	ff_read_map(t_master *master, const char *path)
{
	int		fd;
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
		status = ff_line_to_points(master, line, status);
		free(line);
		if (status == -1)
			error_exit(master, "failed to convert");
	}
	if (master->points_used % master->map_width != 0)
		error_exit(master, "points vs width not matched");
	master->map_height = master->points_used / master->map_width;
	ff_set_xy(master);
	master->file_name = path;
}
