/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:24:15 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/08 14:56:55 by glambrig         ###   ########.fr       */
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

/*This func will be called by threads when nb_p % 2 == 0*/
void	*even(void *phi)
{
	t_philo 	*p;

	p = (t_philo *)phi;
	usleep(5000);
	if (p->id % 2 == 1)	//if it's an odd P
	{
		while (1)
		{
			pthread_mutex_lock(&p->lfork);
			p_status(123, p->id, "has taken a fork");//p->all->start instead of 123
			pthread_mutex_lock(p->rfork);
			p_status(123, p->id, "has taken a fork");//p->all->start instead of 123
			p_status(123, p->id, "is eating");//p->all->start instead of 123
			usleep(p->all->time_to_eat);
			pthread_mutex_unlock(&p->lfork);
			pthread_mutex_unlock(p->rfork);
			p_status(123, p->id, "is sleeping");//p->all->start instead of 123
			usleep(p->all->time_to_sleep);
			p_status(123, p->id, "is thinking");//p->all->start instead of 123
		}

	}
	usleep(p->all->time_to_sleep);
	if (p->id % 2 == 0)
	{
		while (1)
		{
			pthread_mutex_lock(&p->lfork);
			p_status(123, p->id, "has taken a fork");//p->all->start
			pthread_mutex_lock(p->rfork);
			p_status(123, p->id, "has taken a fork");//p->all->start
			p_status(123, p->id, "is eating");//p->all->start
			usleep(p->all->time_to_eat);
			pthread_mutex_unlock(&p->lfork);
			pthread_mutex_unlock(p->rfork);
			p_status(123, p->id, "is sleeping");//p->all->start
			usleep(p->all->time_to_sleep);
			p_status(123, p->id, "is thinking");	//p->all->start
		}
	}
	return (NULL);
}

void	create_threads(t_all *all)
{
	t_philo		*p;
	//t_timeval	start;
	int			i;

	p = all->phi_arr;
	i = 0;
	//printf("nb_p = %d\n", all->nb_p);
	while (i < all->nb_p)
	{
		if (all->nb_p % 2 == 0)
		{
			//printf("in %% 2 == 0\n");
			pthread_create(&(p[i].thr_id), NULL, &even, &all->phi_arr[i]);
		}
		else if (all->nb_p % 2 == 1)
		{
			//printf("in %% 2 == 1\n");
			pthread_create(&(p[i].thr_id), NULL, &even, &all->phi_arr[i]);//CHANGE TO &ODD WHEN THAT FUNC IS WRITTEN
		}
		i++;
	}
	i = 0;
	while (i < all->nb_p)
	{
		pthread_join(p[i].thr_id, NULL);
		i++;
	}
}