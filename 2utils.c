/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <glambrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:25:12 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/17 13:56:03 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_status(long long timestamp, int p_nbr, char *action)
{
	static pthread_mutex_t	moo;
	static int				init;

	if (!init)
	{
		pthread_mutex_init(&moo, NULL);
		init = 1;
	}
	pthread_mutex_lock(&moo);
	ft_putnbr(timestamp);
	ft_putstr("ms ");
	ft_putnbr(p_nbr);
	ft_putchar(' ');
	ft_putstr(action);
	ft_putchar('\n');
	pthread_mutex_unlock(&moo);
}

void	rfork_is_null(t_philo *p, t_timeval start)
{
	usleep(p->all->time_to_die * 1000);
	p_status(calc_elapsed_time(start), p->id, "died");
	free_t_p(p, p->all->nb_p);
	exit(0);
}

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
	if ((calc_elapsed_time(start) - p->last_ate >= p->all->time_to_die)
		|| (p->last_ate == -1 && calc_elapsed_time(start) >= p->all->time_to_die))
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