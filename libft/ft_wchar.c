/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:58:24 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/26 15:20:37 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wstrlen(const wchar_t *wstr)
{
	size_t	len;

	len = 0;
	while (*(wstr++))
		len += 1;
	return (len);
}

char	*ft_wstr2str(const wchar_t *wstr)
{
	size_t	len;
	char	*str;
	char	*rstr;

	len = ft_wstrlen(wstr);
	str = (char *)malloc((len + 1) * sizeof(char));
	rstr = str;
	if (str)
	{
		while (*wstr != L'\0')
			*(str++) = (char)*(wstr++);
		*str = '\0';
	}
	return (rstr);
}

ssize_t	ft_rputnwstr_fd(wchar_t *s, int fd, size_t n)
{
	char	*cstr;
	ssize_t	rv;

	rv = 0;
	if (s)
	{
		cstr = ft_wstr2str(s);
		if (!cstr)
			return (-1);
		rv = (write(fd, cstr, n));
		free(cstr);
	}
	return (rv);
}

void	ft_putwstr_fd(wchar_t *s, int fd)
{
	size_t	len;

	len = ft_wstrlen(s);
	ft_rputnwstr_fd(s, fd, len);
}

void	ft_putnwstr_fd(wchar_t *s, int fd, size_t n)
{
	ft_rputnwstr_fd(s, fd, n);
}
