/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:58:48 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/07 21:42:21 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		diff;
	size_t	i;

	i = 0;
	while (i < n && (*s1 != 0 || *s2 != 0))
	{
		diff = (unsigned char)*(s1) - (unsigned char)*(s2);
		if (*s1 == 0 || *s2 == 0 || diff != 0)
			return (diff);
		s1 += 1;
		s2 += 1;
		i += 1;
	}
	return (0);
}
