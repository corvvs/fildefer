/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:42:20 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/09 18:50:04 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c,
		size_t n)
{
	char	d;

	while (n > 0)
	{
		n -= 1;
		d = *(char *)(src++);
		*(char *)(dst++) = d;
		if (d == (char)c)
			return (dst);
	}
	return (NULL);
}
