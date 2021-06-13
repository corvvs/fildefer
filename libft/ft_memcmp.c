/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:25:10 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/09 18:49:53 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	c2;
	unsigned char	c1;
	int				diff;
	size_t			i;

	i = 0;
	diff = 0;
	while (i < n)
	{
		c1 = *(char *)(s1 + i);
		c2 = *(char *)(s2 + i);
		diff = ((int)c1 - (int)c2);
		if (diff != 0)
			break ;
		i += 1;
	}
	return (diff);
}
