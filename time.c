/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:15:03 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/08 12:15:06 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_timeval	calc_elapsed_time(t_timeval start)
{
	t_timeval	now;
	t_timeval	res;

	gettimeofday(&now, NULL);
	res.tv_sec = now.tv_sec - start.tv_sec;
	res.tv_usec = now.tv_usec - start.tv_usec;
	return (res);
}