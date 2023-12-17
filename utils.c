/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <glambrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:41:31 by glambrig          #+#    #+#             */
/*   Updated: 2023/12/17 16:57:01 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_bzero(void *loc, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		*(char *)(loc + i) = '\0';
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
	ft_bzero((unsigned char *)dest, res);
	return (dest);
}

int	ft_atoi(char *s)
{
	int	res;
	int	i;
	int	sign;

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