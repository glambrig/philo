/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:15:03 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/14 13:25:42 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Calculates elapsed time (in milliseconds)*/
long long	calc_elapsed_time(t_timeval start)
{
	t_timeval	now;
	t_timeval	elapsed;
	long long	res;

	gettimeofday(&now, NULL);
	elapsed.tv_sec = now.tv_sec - start.tv_sec;
	elapsed.tv_usec = now.tv_usec - start.tv_usec;
	res = elapsed.tv_sec * 1000;
	res += elapsed.tv_usec / 1000;
	return (res);
}