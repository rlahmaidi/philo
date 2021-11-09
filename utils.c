#include "struct.h"

int		ft_atoi(const char *str)
{
	int		sign;
	size_t	a;

	sign = 1;
	a = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		a = a * 10 + (*str) - '0';
		str++;
		if (a > 9223372036854775807 && sign == 1)
			return (-1);
		if (sign == -1 && a > 9223372036854775807)
			return (0);
	}
	return ((int)a * sign);
}

int		ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

size_t	ft_strlen(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putnbr(int n)
{
	long i;
	char c;

	i = n;
	if (i < 0)
	{
		write(1, "-", 1);
		i = i * (-1);
	}
	if (i > 9)
	{
		ft_putnbr(i / 10);
	}
	c = i % 10 + 48;
	write(1, &c, 1);
}
