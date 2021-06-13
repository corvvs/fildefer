/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:12:38 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/09 19:03:01 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	k;
	void	*result;

	k = 0;
	result = (void *)s;
	while (k < n)
	{
		if (*(char *)result == (char)c)
			return (result);
		result += 1;
		k += 1;
	}
	return (NULL);
}
