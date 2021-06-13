/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 02:35:27 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/11 21:11:44 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	n;
	char	*cloned;

	n = ft_strlen(src);
	cloned = (char *)ft_calloc(n + 1, sizeof(char));
	if (!cloned)
		return (NULL);
	ft_strlcpy(cloned, src, n + 1);
	return (cloned);
}
