/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 12:40:43 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/09 18:57:00 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	haystack_len;
	size_t	needle_len;
	size_t	i;
	char	*t;

	haystack_len = ft_strlen(str);
	if (len < haystack_len)
		haystack_len = len;
	needle_len = ft_strlen(to_find);
	i = 0;
	t = (char *)str;
	if (needle_len == 0)
		return ((char *)str);
	if (haystack_len < needle_len)
		return (NULL);
	while (*(t + i) != '\0' && i < haystack_len - needle_len + 1)
	{
		if (*(t + i) == *to_find)
			if (ft_strncmp(t + i, to_find, needle_len) == 0)
				return (t + i);
		i += 1;
	}
	return (NULL);
}
