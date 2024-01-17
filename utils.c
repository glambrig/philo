/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <glambrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:41:31 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/17 13:26:06 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(long long n)
{
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

/*lignes 36-37 servent a eviter des calculs de non-entiers*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*dest;
	size_t		res;

	dest = NULL;
	if (!nmemb || !size)
		return (malloc(0));
	res = size * nmemb;
	if (res / size != nmemb)
		return (0);
	dest = malloc(nmemb * size);
	if (!dest)
		return (NULL);
	memset(dest, 0, size);
	return (dest);
}

long long	ft_atoi(char *s)
{
	long long	res;
	int			i;
	int			sign;

	res = 0;
	i = 0;
	sign = 1;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10;
		res += s[i] - '0';
		i++;
	}
	return (res * sign);
}
