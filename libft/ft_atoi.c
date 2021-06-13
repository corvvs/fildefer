/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 02:00:00 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/14 17:55:16 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define ES	10
#define EG	20
#define ED	30

int	ft_atoi(const char *str)
{
	int			state;
	int			sign;
	long long	abs_n;

	state = ES;
	sign = +1;
	abs_n = 0;
	while (*str)
	{
		if (state <= ED && ft_isdigit(*str))
		{
			state = ED;
			abs_n = abs_n * 10 + (*str - '0');
		}
		else if (state <= EG && (*str == '+' || *str == '-'))
		{
			state = ED;
			sign = ',' - *str;
		}
		else if (!(state == ES && ((8 <= *str && *str <= 13) || *str == 32)))
			break ;
		str += 1;
	}
	return (abs_n * sign);
}
