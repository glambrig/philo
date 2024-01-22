/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2algo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:49:29 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/22 16:22:32 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	even_util(t_philo *p, t_timeval start, int i)
{
	pthread_mutex_unlock(&p->all->m_all);
	pthread_mutex_lock(&p->lfork);
	p->has_lfork = 1;
	if (same_routine(p, start) == 1)
		return (1);
	if (p->all->x_each_must_eat != (-1) && i == p->all->x_each_must_eat)
		p->all->sim_done = 1;
	return (0);
}

int	odd_util(t_philo *p, t_timeval start)
{
	usleep(p->all->time_to_die * 10);
	pthread_mutex_lock(&p->lfork);
	pthread_mutex_lock(&p->all->m_all);
	p->has_lfork = 1;
	pthread_mutex_unlock(&p->all->m_all);
	pthread_mutex_lock(&p->all->m_all);
	if (check_death(p, start) == 1)
		return (1);
	pthread_mutex_unlock(&p->all->m_all);
	return (0);
}
