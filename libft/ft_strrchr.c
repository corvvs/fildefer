/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:44:55 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/09 18:46:27 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ans;
	int		i;

	ans = NULL;
	i = 0;
	while (1)
	{
		if (*(s + i) == (char)c)
			ans = (char *)(s + i);
		if (!*(s + i))
			break ;
		i += 1;
	}
	return (ans);
}
