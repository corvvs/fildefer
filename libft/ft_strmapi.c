/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:41:25 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/09 18:48:44 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef unsigned int	t_ui;

char	*ft_strmapi(char const *s, char (*f)(t_ui, char))
{
	t_ui	n;
	char	*applied;
	t_ui	i;

	if (!s)
		return (NULL);
	n = ft_strlen(s);
	applied = (char *)ft_calloc(n + 1, sizeof(char));
	if (!applied)
		return (NULL);
	i = 0;
	while (i < n)
	{
		applied[i] = f(i, s[i]);
		i += 1;
	}
	return (applied);
}
