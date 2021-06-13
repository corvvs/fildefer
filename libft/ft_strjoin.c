/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 19:32:21 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/22 17:32:17 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		n1;
	int		n2;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	n1 = ft_strlen(s1);
	n2 = ft_strlen(s2);
	joined = (char *)ft_calloc(n1 + n2 + 1, sizeof(char));
	if (!joined)
		return (NULL);
	ft_strlcat(joined, s1, n1 + 1);
	ft_strlcat(joined, s2, n1 + n2 + 1);
	return (joined);
}

char	*ft_straddcfront(char c, size_t t, const char *s)
{
	char	*added;
	size_t	len;

	if (!c)
		return (ft_strdup(s));
	len = ft_strlen(s);
	if (t <= len)
		return (ft_strdup(s));
	added = (char *)malloc(sizeof(char) * (t + 1));
	if (added)
	{
		ft_memset(added, c, t - len);
		added[t - len] = '\0';
		ft_strlcat(added, s, t + 1);
	}
	return (added);
}

char	*ft_strjoin_destroy_both(char **s1, char **s2)
{
	char	*joined;

	joined = ft_strjoin(*s1, *s2);
	free(*s1);
	free(*s2);
	return (joined);
}

char	*ft_strjoin_destroy2(const char *s1, char **s2)
{
	char	*joined;

	joined = ft_strjoin(s1, *s2);
	free(*s2);
	return (joined);
}
