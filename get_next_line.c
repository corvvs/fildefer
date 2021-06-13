/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 00:38:06 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/19 06:47:46 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_shift_line(t_tank **top, int fd)
{
	size_t	i;
	char	*line;

	if (!*top || (*top)->fd != fd)
		if (!ft_retrieve_tank(top, fd, 0))
			return (NULL);
	i = (*top)->lhead - 1;
	while (++i < (*top)->ltail)
	{
		if ((*top)->buff[i] == '\n')
			break ;
	}
	if (i < (*top)->ltail || (*top)->read_eof)
	{
		line = ft_strndup((*top)->buff + (*top)->lhead, i - (*top)->lhead);
		if (line)
		{
			(*top)->lhead = i + 1;
			if (i == (*top)->ltail)
				(*top)->tank_stat = 0;
			return (line);
		}
		(*top)->tank_stat = -1;
	}
	return (NULL);
}

int	ft_expand_tank(t_tank *top, size_t n)
{
	size_t	total;
	char	*alter_buffer;
	size_t	i;

	total = top->mem_size;
	while (total < top->ltail + n)
		total <<= 1;
	if (top->mem_size < total)
	{
		alter_buffer = (char *)malloc(total * sizeof(char));
		if (!alter_buffer)
			return (top->tank_stat = -1);
		i = -1;
		while (++i < top->ltail)
			alter_buffer[i] = top->buff[i];
		free(top->buff);
		top->buff = alter_buffer;
		top->mem_size = total;
	}
	return (1);
}

int	ft_store_data(t_tank **top, int fd, char *read_buffer, ssize_t rsize)
{
	ssize_t	i;

	if ((!*top || (*top)->fd != fd))
		if (ft_retrieve_tank(top, fd, 1) != 1)
			return (-1);
	if (rsize == 0)
		(*top)->read_eof = 1;
	if ((*top)->mem_size < rsize + (*top)->ltail)
	{
		i = -1;
		while ((*top)->lhead + (++i) < (*top)->ltail)
			(*top)->buff[i] = (*top)->buff[(*top)->lhead + i];
		(*top)->ltail -= (*top)->lhead;
		(*top)->lhead = 0;
	}
	if (ft_expand_tank(*top, rsize) == -1)
		return (-1);
	i = -1;
	while (++i < rsize)
		(*top)->buff[(*top)->ltail + i] = read_buffer[i];
	(*top)->ltail += rsize;
	return (1);
}

int	ft_read_and_store(t_tank **top, int fd, char **read_buffer)
{
	ssize_t	rsize;

	if (!*read_buffer)
	{
		*read_buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
		if (!*read_buffer)
		{
			if (*top && (*top)->fd == fd)
				(*top)->tank_stat = -1;
			return (-1);
		}
	}
	rsize = read(fd, *read_buffer, BUFFER_SIZE);
	if (rsize == -1 || (rsize == 0 && (!*top || (*top)->fd != fd)))
	{
		if (*top && (*top)->fd == fd)
			(*top)->tank_stat = -1;
		return (rsize);
	}
	return (ft_store_data(top, fd, *read_buffer, rsize));
}

int	get_next_line(int fd, char **line)
{
	static t_tank	*top;
	char			*read_buffer;
	int				rv;

	if (!line || BUFFER_SIZE == 0)
		return (-1);
	read_buffer = NULL;
	rv = 1;
	while (rv == 1)
	{
		*line = ft_shift_line(&top, fd);
		if (*line || (top && top->tank_stat == -1))
			break ;
		rv = ft_read_and_store(&top, fd, &read_buffer);
		if (rv == 0)
			*line = ft_strndup("", 0);
	}
	return (ft_clean(rv, &top, fd, &read_buffer));
}
