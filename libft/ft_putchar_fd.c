/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:15:43 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/29 17:34:18 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define PUTCHAR_BULK	4096

ssize_t	ft_rputchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

void	ft_putchar_fd(char c, int fd)
{
	ft_rputchar_fd(c, fd);
}

ssize_t	ft_rputchar_ntimes_fd(char c, size_t times, int fd)
{
	char	cs[PUTCHAR_BULK];
	size_t	n;
	ssize_t	written;
	size_t	rv;

	n = PUTCHAR_BULK;
	rv = 0;
	if (times < PUTCHAR_BULK)
		n = times;
	ft_memset(cs, c, n);
	while (times > 0)
	{
		if (times < PUTCHAR_BULK)
			n = times;
		written = write(fd, cs, n);
		if (written < 0)
			return (-1);
		rv += written;
		times -= n;
	}
	return (rv);
}

void	ft_putchar_ntimes_fd(char c, size_t times, int fd)
{
	ft_rputchar_ntimes_fd(c, times, fd);
}
