/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 00:31:25 by yokawada          #+#    #+#             */
/*   Updated: 2021/06/10 23:56:40 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 512

typedef struct s_tank
{
	char			*buff;
	int				fd;
	size_t			lhead;
	size_t			ltail;
	size_t			mem_size;
	int				read_eof;
	int				tank_stat;
	size_t			std_lsize;
	struct s_tank	*prev;
	struct s_tank	*next;
}	t_tank;

int		get_next_line(int fd, char **line);
int		ft_retrieve_tank(t_tank **top, int fd, int create);
char	*ft_shift_line(t_tank **top, int fd);
char	*ft_strndup(char *mem, size_t n);
void	ft_elevate(t_tank **top, t_tank *tank);
int		ft_push_front(t_tank **top, int fd);
int		ft_read_and_store(t_tank **top, int fd, char **read_buffer);
int		ft_store_data(t_tank **top, int fd, char *read_buffer, ssize_t rsize);
int		ft_expand_tank(t_tank *top, size_t n);
int		ft_clean(int rv, t_tank **top, int fd, char **read_buffer);

#endif
