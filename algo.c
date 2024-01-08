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
	printf("in even\n");
	t_philo *p;

	p = (t_philo *)phi;
	/*Wait for all threads to get here*/
	static int	here;
	if (!here)
		here = 0;
	here++;
	while (here != p->all->nb_p)
		usleep(5);
	/*All threads are here*/
	printf("hello!!\n");
	if (p->id % 2 == 1)	//if it's an odd P
	{
		while (1)
		{
			pthread_mutex_lock(&p->lfork);
			p_status(p->all->start, p->id, "has taken a fork");
			pthread_mutex_lock(p->rfork);
			p_status(p->all->start, p->id, "has taken a fork");
			p_status(p->all->start, p->id, "is eating");
			usleep(p->all->time_to_eat);
			pthread_mutex_unlock(&p->lfork);
			pthread_mutex_unlock(p->rfork);
			p_status(p->all->start, p->id, "is sleeping");
			usleep(p->all->time_to_sleep);
			p_status(p->all->start, p->id, "is thinking");
		}

	}
	usleep(p->all->time_to_sleep);
	if (p->id % 2 == 0)
	{
		while (1)
		{
			pthread_mutex_lock(&p->lfork);
			p_status(p->all->start, p->id, "has taken a fork");
			pthread_mutex_lock(p->rfork);
			p_status(p->all->start, p->id, "has taken a fork");
			p_status(p->all->start, p->id, "is eating");
			usleep(p->all->time_to_eat);
			pthread_mutex_unlock(&p->lfork);
			pthread_mutex_unlock(p->rfork);
			p_status(p->all->start, p->id, "is sleeping");
			usleep(p->all->time_to_sleep);
			p_status(p->all->start, p->id, "is thinking");	
		}
	}
	return (NULL);
}

void	create_threads(t_all *all)
{
	t_timeval	start;
	t_philo		*p;
	int			i;

	p = all->phi_arr;
	i = 0;
	gettimeofday(&all->start, NULL);
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
		pthread_detach(p[i].thr_id);	//Lets to OS clean up thread resources if main process ends
		i++;
	}
}