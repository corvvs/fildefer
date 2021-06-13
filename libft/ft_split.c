/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokawada <yokawada@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:54:47 by yokawada          #+#    #+#             */
/*   Updated: 2021/04/11 23:55:53 by yokawada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define MODE_WORD	10
#define MODE_DELIM	100

static int	ft_is_delimiter(char c, const char needle)
{
	return (!needle || needle == c);
}

static int	ft_word_len(const char *str, char c)
{
	int		i;

	i = -1;
	while (*(str + (++i)))
		if (ft_is_delimiter(c, *(str + i)))
			break ;
	return (i);
}

static int	ft_word_count(const char *str, char c)
{
	int		waiting;
	int		i;
	int		word_count;

	waiting = MODE_WORD;
	i = 0;
	word_count = 0;
	while (*(str + i))
	{
		if (waiting == MODE_WORD && !ft_is_delimiter(c, *(str + i)))
		{
			waiting = MODE_DELIM;
			word_count += 1;
		}
		else if (waiting == MODE_DELIM && ft_is_delimiter(c, *(str + i)))
			waiting = MODE_WORD;
		i += 1;
	}
	return (word_count);
}

static char	*ft_strdup_r(char **dst, const char *src, char c, int rest_words)
{
	int		i;
	int		n;
	char	*cloned;
	void	*succ;

	while (*(src) == c)
		src += 1;
	n = ft_word_len(src, c);
	cloned = (char *)ft_calloc(n + 1, sizeof(char));
	if (!cloned)
		return (NULL);
	i = -1;
	while (++i < n)
		cloned[i] = src[i];
	*dst = cloned;
	if (rest_words > 0)
	{
		succ = ft_strdup_r(dst + 1, src + n, c, rest_words - 1);
		if (!succ)
		{
			free(cloned);
			return (NULL);
		}
	}
	return (cloned);
}

char	**ft_split(char const *str, char c)
{
	int		word_count;
	char	**splitted;

	if (!str)
		return (NULL);
	word_count = ft_word_count(str, c);
	splitted = (char **)ft_calloc(word_count + 1, sizeof(char *));
	if (word_count > 0 && !ft_strdup_r(splitted, str, c, word_count - 1))
	{
		free(splitted);
		return (NULL);
	}
	return (splitted);
}
