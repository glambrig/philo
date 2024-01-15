/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:24:15 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/15 13:38:56 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Events:
	-P started eating
	-P started sleeping
	-P started thinking
	-P died
	-P picked up fork
*/

/*For odd number:

1. Odd numbered p's eat starting at p1, except the last (on the left of p1), who has to wait.
2. p's on the right of the ones that just ate now eat.
3. again, the ones of the right of those who ate in step 2 now eat (this includes the last one before p1)
4. back to step 1

For even number:

1. Odd numbered p's eat
2. Even numbered p's eat
3. Back to step 1*/

/*Detaches all threads, and unlocks all mutexes*/
void	detach_t_unlock_m_all(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->all->nb_p)
	{
		pthread_mutex_unlock(&p->all->phi_arr[i].lfork);
		pthread_detach(p->all->phi_arr[i].thr_id);
		i++;
	}
}

int	check_death(t_philo *p, t_timeval start)
{
	pthread_mutex_lock(&p->all->m_dead);
	if (calc_elapsed_time(start) - p->last_ate >= p->all->time_to_die)
	{
		p->all->dead = 1;
		p_status(calc_elapsed_time(start), p->id, "died");
		detach_t_unlock_m_all(p);
		free_t_p(p, p->all->nb_p);
		exit(0);
		return (1);
	}
	pthread_mutex_unlock(&p->all->m_dead);
	return (0);
}

void	*odd(void *phi)
{
	t_philo 	*p;
	t_timeval	start;
	int			i;

	p = (t_philo *)phi;
	gettimeofday(&start, NULL);
	i = 0;
	while (p->all->dead != 1 && i++ < p->all->times_each_must_eat)
	{
		pthread_mutex_lock(&p->lfork);
		p->has_lfork = 1;
		check_death(p, start);
		p_status(calc_elapsed_time(start), p->id, "has taken a LEFT fork");
		if (p->rfork != NULL)
			pthread_mutex_lock(p->rfork);
		else	//if there's only one P rfork == NULL
		{
			usleep(p->all->time_to_die * 1000);	//x1000 because usleep takes MICROseconds
			p_status(calc_elapsed_time(start), p->id, "died");
			free_t_p(p, p->all->nb_p);
			exit(0);
		}
		p->has_rfork = 1;
		check_death(p, start);
		p_status(calc_elapsed_time(start), p->id, "has taken a RIGHT fork");
		p_status(calc_elapsed_time(start), p->id, "is eating");
		p->last_ate = calc_elapsed_time(start);
		usleep(p->all->time_to_eat * 1000);
		check_death(p, start);
		p_status(calc_elapsed_time(start), p->id, "is sleeping");
		pthread_mutex_unlock(&p->lfork);
		pthread_mutex_unlock(p->rfork);
		p->has_lfork = 0;
		p->has_rfork = 0;
		check_death(p, start);
		usleep(p->all->time_to_sleep * 1000);
		p_status(calc_elapsed_time(start), p->id, "is thinking");
	}
	detach_t_unlock_m_all(p);
	free_t_p(p, p->all->nb_p);
	exit(0);
	return (NULL);
}

/*This func will be called by threads when nb_p % 2 == 0*/
void	*even(void *phi)
{
	t_philo 	*p;
	t_timeval	start;
	int			i;

	p = (t_philo *)phi;
	gettimeofday(&start, NULL);
	i = 0;
	while (p->all->dead != 1 && i++ < p->all->times_each_must_eat)
	{
		pthread_mutex_lock(&p->lfork);
		p->has_lfork = 1;
		check_death(p, start);
		p_status(calc_elapsed_time(start), p->id, "has taken a LEFT fork");
		if (p->rfork != NULL)
			pthread_mutex_lock(p->rfork);
		else	//if there's only one P rfork == NULL
		{
			usleep(p->all->time_to_die * 1000);	//x1000 because usleep takes MICROseconds
			p_status(calc_elapsed_time(start), p->id, "died");
			free_t_p(p, p->all->nb_p);
			exit(0);
		}
		p->has_rfork = 1;
		check_death(p, start);
		p_status(calc_elapsed_time(start), p->id, "has taken a RIGHT fork");
		p_status(calc_elapsed_time(start), p->id, "is eating");
		p->last_ate = calc_elapsed_time(start);
		usleep(p->all->time_to_eat * 1000);
		check_death(p, start);
		p_status(calc_elapsed_time(start), p->id, "is sleeping");
		pthread_mutex_unlock(&p->lfork);
		pthread_mutex_unlock(p->rfork);
		p->has_lfork = 0;
		p->has_rfork = 0;
		check_death(p, start);
		usleep(p->all->time_to_sleep * 1000);
		p_status(calc_elapsed_time(start), p->id, "is thinking");
	}
	detach_t_unlock_m_all(p);
	free_t_p(p, p->all->nb_p);
	exit(0);
	return (NULL);
}

void	create_threads(t_all *all)
{
	t_philo		*p;
	int			i;

	p = all->phi_arr;
	i = 0;
	while (i < all->nb_p)
	{
		if (all->nb_p % 2 == 0)
			pthread_create(&(p[i].thr_id), NULL, &even, &all->phi_arr[i]);
		else if (all->nb_p % 2 == 1)
		{
			pthread_create(&(p[i].thr_id), NULL, &odd, &all->phi_arr[i]);
			usleep(10000);
		}
		i++;
	}
	//usleep(10000);
	i = 0;
	while (i < all->nb_p)
	{
		pthread_join(p[i].thr_id, NULL);
		i++;
	}
}