/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:24:15 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/18 12:05:07 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	same_routine(t_philo *p, t_timeval start)
{
	p_status(calc_elapsed_time(start), p->id, "has taken a fork");
	p_status(calc_elapsed_time(start), p->id, "is eating");
	p->last_ate = calc_elapsed_time(start);
	usleep(p->all->time_to_eat * 1000);
	if (check_death(p, start) == 1)
		return ;
	p_status(calc_elapsed_time(start), p->id, "is sleeping");
	pthread_mutex_unlock(&p->lfork);
	pthread_mutex_unlock(p->rfork);
	if (check_death(p, start) == 1)
		return ;
	usleep(p->all->time_to_sleep * 1000);
	p_status(calc_elapsed_time(start), p->id, "is thinking");
}

/*
	usleep gives time for even p's to start eating
	rfork == NULL means that there's only one philosopher
*/
void	odd(t_philo *p)
{
	t_timeval	start;
	int			i;

	gettimeofday(&start, NULL);
	i = 0;
	while (p->all->dead != 1 && i++ < p->all->times_each_must_eat)
	{
		usleep(p->all->time_to_die * 10);
		pthread_mutex_lock(&p->lfork);
		if (check_death(p, start) == 1)
			return ;
		p_status(calc_elapsed_time(start), p->id, "has taken a fork");
		if (p->rfork != NULL)
			pthread_mutex_lock(p->rfork);
		else
			rfork_is_null(p, start);
		if (check_death(p, start) == 1)
			return ;
		same_routine(p, start);
	}
	//detach_t_unlock_m_all(p);
	//free_t_p(p, p->all->nb_p);
	return ;
	//exit(0);
}

void	even(t_philo *p)
{
	t_timeval	start;
	int			i;

	gettimeofday(&start, NULL);
	i = 0;
	while (p->all->dead != 1 && (i++ < p->all->times_each_must_eat
			|| p->all->times_each_must_eat == (-1)))
	{
		if (p->rfork != NULL)
		{
			pthread_mutex_lock(p->rfork);
			p_status(calc_elapsed_time(start), p->id, "has taken a fork");
		}
		else
			rfork_is_null(p, start);
		if (check_death(p, start) == 1)
			return ;
		pthread_mutex_lock(&p->lfork);
		same_routine(p, start);
	}
	//detach_t_unlock_m_all(p);
	//free_t_p(p, p->all->nb_p);
	return ;
	//exit(0);
}

void	*thread_func(void *phi)
{
	t_philo	*p;

	p = (t_philo *)phi;
	if (p->id % 2 == 0)
		even(p);
	else
		odd(p);
	return (NULL);
}

void	create_threads(t_all *all)
{
	t_philo	*p;
	int		i;

	p = all->phi_arr;
	i = 0;
	while (i < all->nb_p)
	{
		pthread_create(&(p[i].thr_id), NULL, &thread_func, &all->phi_arr[i]);
		i++;
	}
	usleep(all->time_to_die * 1000);
	i = 0;
	while (i < all->nb_p && all->dead != 1)
	{
		pthread_join(p[i].thr_id, NULL);
		i++;
	}
}
