/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:01:47 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/07 17:12:49 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_error(char *s)
{
	ft_putstr("Error: ");
	ft_putstr(s);
	exit(0);
}

void	check_instakill(t_all *all)
{
	int	i;

	i = 0;
	if (all->time_to_die == 0)
	{
		while (i < all->nb_p)
		{
			//printf("0ms %d died\n", i + 1);	//all->phi_arr[i].id
			ft_putstr("0ms ");
			ft_putnbr(i + 1);
			ft_putstr(" has died\n");
			i++;
		}
		exit(0);
	}
}

void	check_negatives(t_all *all)
{
	if (all->nb_p <= 0 || all->time_to_die < 0 || all->time_to_eat < 0
		|| all->time_to_sleep < 0)
		write_error("Negative number as input");
	if (all->times_each_must_eat == 0 && all->times_each_must_eat < 0)
	{
		printf("each must eat = %d\n", all->times_each_must_eat);///////
		if (all->times_each_must_eat == 0)
			exit(0);
		write_error("Negative number as input (times_each_must_eat)");
	}
}

void	error_checks(t_all *all)
{
	if (all->nb_p == 0)
		write_error("There must be at least one philosopher\n");
	check_negatives(all);
	check_instakill(all);
}
