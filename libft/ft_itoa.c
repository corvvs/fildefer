/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 10:24:09 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/22 21:28:50 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define DIGITS "0123456789abcdefghijklmnopqrstuvwxyz"

static size_t	size_of_uint(t_ull n, int base)
{
	int	size;

	if (n == 0)
		return (1);
	size = 0;
	while (n)
	{
		size += 1;
		n /= base;
	}
	return (size);
}

char	*ft_uitoa_base(t_ull n, int base, int negative, ssize_t least)
{
	int		size;
	int		s0;
	char	*a;

	size = size_of_uint(n, base);
	if (least > size)
		size = least;
	size += !!negative;
	a = (char *)ft_calloc(size + 1, sizeof(char));
	if (a)
	{
		ft_memset(a, '0', size);
		if (negative)
			a[0] = '-';
		s0 = negative;
		size -= 1;
		while (s0 <= size)
		{
			a[size--] = DIGITS[n % base];
			if (n == 0)
				break ;
			n /= base;
		}
	}
	return (a);
}

char	*ft_itoa_base(long long n, int base, ssize_t least)
{
	t_ull	abs;
	int		negative;

	negative = n < 0;
	if (negative)
		abs = -n;
	else
		abs = n;
	return (ft_uitoa_base(abs, base, negative, least));
}

char	*ft_itoa(int n)
{
	return (ft_itoa_base(n, 10, 0));
}
