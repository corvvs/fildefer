/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:55:01 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/27 00:49:00 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!dst && !src)
		return (NULL);
	if (len > 0 && dst != src)
	{
		if (dst > src)
			while (len-- > 0)
				*(unsigned char *)(dst + len) = *(unsigned char *)(src + len);
		else
			ft_memcpy(dst, src, len);
	}
	return (dst);
}
