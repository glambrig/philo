/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:25:12 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/22 16:22:15 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_status(long long timestamp, int p_nbr, char *action, t_philo *p)
{
	pthread_mutex_lock(&p->all->m_status);
	ft_putnbr(timestamp);
	ft_putstr("ms ");
	ft_putnbr(p_nbr);
	ft_putchar(' ');
	ft_putstr(action);
	ft_putchar('\n');
	pthread_mutex_unlock(&p->all->m_status);
}

int	rfork_is_null(t_philo *p, t_timeval start)
{
	usleep(p->all->time_to_die * 1000);
	p_status(calc_elapsed_time(start), p->id, "died", p);
	if (p->has_lfork == 1)
		pthread_mutex_unlock(&p->lfork);
	else if (p->has_rfork == 1)
		pthread_mutex_unlock(p->rfork);
	p->all->dead = 1;
	p->all->sim_done = 1;
	return (1);
}

/*Each p unlocks its own lfork mutex, if it's locked.
	Also unlocks rfork mutex, if IT has been the one to lock it.*/
void	detach_t_unlock_m_all(t_philo *p)
{
	pthread_mutex_lock(&p->all->m_unlock);
	if (p->has_lfork == 1)
	{
		pthread_mutex_unlock(&p->lfork);
		p->has_lfork = 0;
	}
	if (p->id != p->all->nb_p)
	{
		if (p->has_rfork == 1)
		{
			pthread_mutex_unlock(p->rfork);
			p->has_rfork = 0;
		}
	}
	else if (p->id == p->all->nb_p)
	{
		if (p->has_rfork == 1 && p->all->phi_arr[0].has_lfork == 0)
		{
			pthread_mutex_unlock(p->rfork);
			p->has_rfork = 0;
		}
	}
	pthread_mutex_unlock(&p->all->m_unlock);
}

int	check_death(t_philo *p, t_timeval start)
{
	pthread_mutex_lock(&p->all->m_dead);
	if (p->all->dead == 1 || (calc_elapsed_time(start) - p->last_ate
			>= p->all->time_to_die)
		|| (p->last_ate == -1 && calc_elapsed_time(start)
			>= p->all->time_to_die))
	{
		if (p->all->dead == 0)
			p_status(calc_elapsed_time(start), p->id, "died", p);
		p->all->dead = 1;
		p->all->sim_done = 1;
		detach_t_unlock_m_all(p);
		pthread_mutex_unlock(&p->all->m_dead);
		pthread_mutex_unlock(&p->all->m_all);
		return (1);
	}
	pthread_mutex_unlock(&p->all->m_dead);
	return (0);
}
