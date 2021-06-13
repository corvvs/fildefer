/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:31:45 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/09 18:49:48 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*idst;

	idst = dst;
	if (dst || src)
	{
		while (n > 0)
		{
			*(char *)(dst++) = *(char *)(src++);
			n -= 1;
		}
	}
	return (idst);
}
