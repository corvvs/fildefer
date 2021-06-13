/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 13:02:12 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/09 18:57:36 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_size;
	size_t	rv;
	size_t	j;

	dest_size = ft_strlen(dest);
	rv = dest_size;
	if (size <= dest_size)
		rv = size;
	rv += ft_strlen(src);
	if (size == 0)
		return (rv);
	j = 0;
	while (j + dest_size < size - 1)
	{
		if (*(src + j) == '\0')
			break ;
		*(dest + dest_size + j) = *(src + j);
		j += 1;
	}
	if (dest_size < size)
		*(dest + dest_size + j) = '\0';
	return (rv);
}
