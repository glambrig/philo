/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:24:15 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/22 15:50:17 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	same_routine(t_philo *p, t_timeval start)
{
	pthread_mutex_lock(&p->all->m_all);
	if (check_death(p, start) == 1)
	 	return (1);
	pthread_mutex_unlock(&p->all->m_all);
	p_status(calc_elapsed_time(start), p->id, "has taken a fork", p);
	p_status(calc_elapsed_time(start), p->id, "is eating", p);
	p->last_ate = calc_elapsed_time(start);
	usleep(p->all->time_to_eat * 1000);
	pthread_mutex_lock(&p->all->m_all);
	if (check_death(p, start) == 1)
		return (1);
	pthread_mutex_unlock(&p->all->m_all);
	p_status(calc_elapsed_time(start), p->id, "is sleeping", p);
	p->has_lfork = 0;
	p->has_rfork = 0;
	pthread_mutex_unlock(&p->lfork);
	pthread_mutex_unlock(p->rfork);
	pthread_mutex_lock(&p->all->m_all);
	if (check_death(p, start) == 1)
		return (1);
	pthread_mutex_unlock(&p->all->m_all);
	usleep(p->all->time_to_sleep * 1000);
	p_status(calc_elapsed_time(start), p->id, "is thinking", p);
	return (0);
}

/*
	usleep gives time for even p's to start eating
	rfork == NULL means that there's only one philosopher
*/
void	odd(t_philo *p, t_timeval start)
{
	int			i;

	i = 0;
	while (p->all->dead != 1 && i++ < p->all->times_each_must_eat)
	{
		odd_util(p, start);
		p_status(calc_elapsed_time(start), p->id, "has taken a fork", p);
		if (p->rfork != NULL)
		{
			pthread_mutex_lock(p->rfork);
			pthread_mutex_lock(&p->all->m_all);//
			p->has_rfork = 1;
			pthread_mutex_unlock(&p->all->m_all);//
		}
		else if (rfork_is_null(p, start) == 1)
			return ;
		pthread_mutex_lock(&p->all->m_all);
		if (check_death(p, start) == 1)
			return ;
		pthread_mutex_unlock(&p->all->m_all);
		if (same_routine(p, start) == 1)
			return ;
		if (p->all->times_each_must_eat != (-1) && i == p->all->times_each_must_eat)
			p->all->sim_done = 1;
	}
}

void	even(t_philo *p, t_timeval start)
{
	int			i;

	i = 0;
	while (p->all->dead != 1 && (i++ < p->all->times_each_must_eat
			|| p->all->times_each_must_eat == (-1)) && p->all->sim_done != 1)
	{
		if (p->rfork != NULL)
		{
			pthread_mutex_lock(p->rfork);
			p->has_rfork = 1;
			p_status(calc_elapsed_time(start), p->id, "has taken a fork", p);
		}
		else if (rfork_is_null(p, start))
			return ;
		pthread_mutex_lock(&p->all->m_all);
		if (check_death(p, start) == 1)
		{
			p->has_rfork = 0;
			pthread_mutex_unlock(p->rfork);
			return ;
		}
		if (even_util(p, start, i) == 1)
			return ;
	}
}

void	*thread_func(void *phi)
{
	t_philo	*p;
	t_timeval	start;

	p = (t_philo *)phi;
	gettimeofday(&start, NULL);
	if (p->id % 2 == 0)
		even(p, start);
	else
		odd(p, start);
	return (NULL);
}

int	create_threads(t_all *all)
{
	t_philo	*p;
	int		i;

	p = all->phi_arr;
	i = 0;
	while (i < all->nb_p)
	{
		if (pthread_create(&(p[i].thr_id), NULL, &thread_func, &all->phi_arr[i]) != 0)
			return (write_error("pthread_create failed"));
		i++;
	}
	usleep(all->time_to_die * 1000);
	while (all->dead == 0 && all->sim_done == 0)
		usleep(1000);
	i = 0;
	while (i < all->nb_p)
	{
		if (pthread_join(p[i].thr_id, NULL) != 0)
			return (write_error("pthread_join failed"));
		i++;
	}
	if (all->dead == 1)
		return (1);
	return (0);
}
