/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:46:49 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/09 19:16:47 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef unsigned int	t_ui;

char	*ft_substr(char const *s, t_ui start, size_t len)
{
	t_ui	n;
	int		sslen;
	char	*ss;

	if (!s)
		return (NULL);
	n = ft_strlen(s);
	if (n <= start)
		sslen = 0;
	else if (n - start <= len)
		sslen = n - start;
	else
		sslen = len;
	if (sslen < 0)
		return (NULL);
	ss = (char *)ft_calloc(sslen + 1, sizeof(char));
	if (!ss)
		return (NULL);
	ft_strlcpy(ss, s + start, sslen + 1);
	return (ss);
}
