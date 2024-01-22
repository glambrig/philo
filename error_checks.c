/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:01:47 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/22 16:23:09 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_error(char *s)
{
	ft_putstr("Error: ");
	ft_putstr(s);
	ft_putchar('\n');
	return (1);
}

int	check_instakill(t_all *all)
{
	int	i;

	i = 0;
	if (all->time_to_die == 0)
	{
		while (i < all->nb_p)
		{
			ft_putstr("0ms ");
			ft_putnbr(i + 1);
			ft_putstr(" has died\n");
			i++;
		}
		return (1);
	}
	return (0);
}

int	check_negatives(t_all *all)
{
	if (all->nb_p <= 0 || all->time_to_die < 0 || all->time_to_eat < 0
		|| all->time_to_sleep < 0)
	{
		write_error("Negative number as input");
		return (1);
	}
	if (all->x_each_must_eat == 0 && all->x_each_must_eat < 0)
	{
		if (all->x_each_must_eat == 0)
			return (1);
		write_error("Negative number as input (x_each_must_eat)");
		return (1);
	}
	return (0);
}

int	error_checks(t_all *all)
{
	if (all->nb_p == 0)
		write_error("There must be at least one philosopher\n");
	if (check_negatives(all) == 1)
		return (1);
	if (check_instakill(all) == 1)
		return (1);
	return (0);
}
