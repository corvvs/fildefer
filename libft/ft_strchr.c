/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:43:10 by yokawada          #+#    #+#             */
/*   Updated: 2021/06/11 03:39:45 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (1)
	{
		if (*s == (char)c)
			return ((char *)s);
		if (!*s)
			break ;
		s += 1;
	}
	return (NULL);
}

/*
 * find first occurence of a character `c` in a string `s`,
 * and returns its index.
 */
int	ft_stri(const char *s, int c)
{
	int	i;

	i = 0;
	while (1)
	{
		if (*s == (char)c)
			return (i);
		if (!*s)
			break ;
		s += 1;
		i += 1;
	}
	return (-1);
}

char	*ft_strchr_nn(const char *s, int c)
{
	if (!c)
		return (NULL);
	return (ft_strchr(s, c));
}
