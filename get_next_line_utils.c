/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 09:33:26 by yokawada          #+#    #+#             */
/*   Updated: 2021/06/10 23:56:19 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define INITIAL_SIZE	1024

char	*ft_strndup(char *mem, size_t n)
{
	char	*cloned;
	size_t	i;

	cloned = malloc((n + 1) * sizeof(char));
	if (cloned)
	{
		i = -1;
		while (++i < n)
			cloned[i] = mem[i];
		cloned[n] = '\0';
	}
	return (cloned);
}

void	ft_elevate(t_tank **top, t_tank *tank)
{
	if (!(tank->prev))
		return ;
	tank->prev->next = tank->next;
	if (tank->next)
		tank->next->prev = tank->prev;
	tank->next = *top;
	tank->prev = NULL;
	if (*top)
		(*top)->prev = tank;
	*top = tank;
}

int	ft_push_front(t_tank **top, int fd)
{
	t_tank	*new;

	new = (t_tank *)malloc(sizeof(t_tank));
	if (new)
	{
		new->buff = malloc(INITIAL_SIZE * sizeof(char));
		if (new->buff)
		{
			new->fd = fd;
			new->lhead = 0;
			new->ltail = 0;
			new->mem_size = INITIAL_SIZE;
			new->read_eof = 0;
			new->tank_stat = 1;
			new->std_lsize = 0;
			new->prev = NULL;
			new->next = *top;
			if (*top)
				(*top)->prev = new;
			*top = new;
			return (1);
		}
		free(new);
	}
	return (-1);
}

int	ft_retrieve_tank(t_tank **top, int fd, int create)
{
	t_tank	*head;

	head = *top;
	while (head && head->fd != fd)
		head = head->next;
	if (head)
	{
		ft_elevate(top, head);
		return (1);
	}
	else if (!create)
		return (0);
	else
		return (ft_push_front(top, fd) == 1);
}

int	ft_clean(int rv, t_tank **top, int fd, char **read_buffer)
{
	int		rrv;
	t_tank	*tmp;

	rrv = rv;
	if (*read_buffer)
		free(*read_buffer);
	if (*top && (*top)->fd == fd)
	{
		rrv = (*top)->tank_stat;
		if (rrv <= 0)
		{
			tmp = *top;
			*top = tmp->next;
			if (tmp->next)
				tmp->next->prev = NULL;
			tmp->next = NULL;
			free(tmp->buff);
			free(tmp);
		}
	}
	return (rrv);
}
