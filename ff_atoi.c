#include "fdf.h"
#define DIGITS "0123456789ABCDEF"

int	ff_atoi_d(char *str, int *d)
{
	int			negative;
	int			i;
	long long	n;

	negative = *str == '-';
	str += negative;
	n = 0;
	while (*str)
	{
		i = ft_stri(DIGITS, *(str++));
		if (i < 0 || 10 <= i)
			return (0);
		n = n * 10 + i;
		if (-n < INT_MIN)
			return (0);
	}
	if (negative)
		n = -n;
	if (n < INT_MIN || INT_MAX < n)
		return (0);
	*d = (int)n;
	return (1);
}

int	ff_atoi_hd(char *str, uint32_t *hd)
{
	int			i;
	uint64_t	n;

	n = 0;
	if (str[0] == '0' && str[1] == 'x')
		str += 2;
	while (*str)
	{
		i = ft_stri(DIGITS, ft_toupper(*(str++)));
		if (i < 0 || 16 <= i)
			return (0);
		n = n * 16 + i;
		if (UINT32_MAX < n)
			return (0);
	}
	*hd = (uint32_t)n;
	return (1);
}
