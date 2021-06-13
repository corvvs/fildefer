/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 23:05:31 by corvvs            #+#    #+#             */
/*   Updated: 2021/04/09 19:15:00 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (dest || src)
	{
		while (0 < size && i < size - 1)
		{
			if (*(src + i) == '\0')
				break ;
			*(dest + i) = *(src + i);
			i += 1;
		}
		if (size > 0)
			*(dest + i) = '\0';
		while (*(src + i) != '\0')
			i += 1;
	}
	return (i);
}
