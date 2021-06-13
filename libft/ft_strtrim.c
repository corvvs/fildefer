/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:39:17 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/11 23:55:38 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_contained(char c, char const *set)
{
	while (*set)
		if (*(set++) == c)
			return (1);
	return (0);
}

static char	*trim_str(char const *s1, int from, int to)
{
	int		n;
	char	*trimmed;

	n = to - from + 1;
	if (from > to)
		n = 0;
	trimmed = (char *)ft_calloc(n + 1, sizeof(char));
	if (trimmed)
		ft_strlcpy(trimmed, s1 + from, n + 1);
	return (trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		n;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	n = ft_strlen(s1);
	i = -1;
	while (++i < n)
		if (!is_contained(*(s1 + i), set))
			break ;
	j = n;
	while (0 <= --j)
		if (!is_contained(*(s1 + j), set))
			break ;
	return (trim_str(s1, i, j));
}
