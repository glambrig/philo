/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:41:31 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/08 14:17:33 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

//was t_timeval timestamp
void	p_status(int timestamp, int p_nbr, char *action)
{
	static pthread_mutex_t	moo;
	static int				init;

	if (!init)
	{
		pthread_mutex_init(&moo, NULL);
		init = 1;
	}
	pthread_mutex_lock(&moo);
	//ft_putnbr(timestamp.tv_usec);
	ft_putnbr(timestamp);
	ft_putstr("ms ");
	ft_putnbr(p_nbr);
	ft_putchar(' ');
	ft_putstr(action);
	ft_putchar('\n');
	pthread_mutex_unlock(&moo);
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
