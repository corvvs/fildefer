/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:18:56 by yokawada          #+#    #+#             */
/*   Updated: 2021/06/10 23:56:58 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_rputstr_fd(char *s, int fd)
{
	if (s)
		return (write(fd, s, ft_strlen(s)));
	return (0);
}

ssize_t	ft_rputnstr_fd(char *s, int fd, size_t n)
{
	if (s)
		return (write(fd, s, n));
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	ft_rputstr_fd(s, fd);
}

void	ft_putnstr_fd(char *s, int fd, size_t n)
{
	ft_rputnstr_fd(s, fd, n);
}

void	ft_putstr_endl_fd(int fd, char *str)
{	
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
}
