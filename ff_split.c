#include "fdf.h"
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

static void	ff_strdup_r(char **dst, char *src, char c, int rest_words)
{
	int		n;

	while (*(src) == c)
		src += 1;
	n = ft_word_len(src, c);
	src[n] = '\0';
	*dst = src;
	if (rest_words > 0)
		ff_strdup_r(dst + 1, src + n + 1, c, rest_words - 1);
}

char	**ff_destructive_split(char *str, char c)
{
	int		word_count;
	char	**splitted;

	if (!str)
		return (NULL);
	word_count = ft_word_count(str, c);
	splitted = (char **)ft_calloc(word_count + 1, sizeof(char *));
	if (splitted && word_count > 0)
		ff_strdup_r(splitted, str, c, word_count - 1);
	return (splitted);
}
