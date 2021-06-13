/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:26:28 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/16 18:48:25 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	n;
	void	*allocated;

	n = count * size;
	if (n == 0)
		n = 1;
	allocated = malloc(n);
	if (allocated)
		ft_bzero(allocated, count * size);
	return (allocated);
}
