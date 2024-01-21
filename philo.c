/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <glambrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:36:30 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/21 16:24:03 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Frees allocated memory and destroys mutexes (forks)*/
void	free_t_p(t_philo *p, int nb_p)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&p->all->m_dead);
	pthread_mutex_destroy(&p->all->m_all);
	pthread_mutex_destroy(&p->all->m_status);
	while (i < nb_p)
	{
		// if (&(p[i].lfork) != NULL)
		pthread_mutex_destroy(&(p[i].lfork));
		i++;
	}
	free(p->all->phi_arr);
}

void	set_fork_pointers(t_philo *phi_arr, int nb_phi)
{
	int	i;

	i = 0;
	if (nb_phi == 1)
	{
		phi_arr[0].rfork = NULL;
		phi_arr[0].has_lfork = 0;
		phi_arr[0].has_rfork = 0;
		return ;
	}
	while (i < nb_phi)
	{
		phi_arr[i].rfork = &phi_arr[i + 1].lfork;
		phi_arr[i].has_lfork = 0;
		phi_arr[i].has_rfork = 0;
		i++;
	}
	phi_arr[nb_phi].rfork = &phi_arr[0].lfork;
}

void	init_forks(t_philo *phi_arr, int nb_phi)
{
	int	i;

	i = 0;
	pthread_mutex_init(&phi_arr->all->m_dead, NULL);
	pthread_mutex_init(&phi_arr->all->m_all, NULL);
	pthread_mutex_init(&phi_arr->all->m_status, NULL);
	while (i < nb_phi)
	{
		if (pthread_mutex_init(&(phi_arr[i].lfork), NULL) != 0)
		{
			write_error("pthread_mutex_init failed");
			return ;
		}
		i++;
	}
	//pthread_mutex_init(phi_arr[i].rfork, NULL); test
}

/*Allocates the array of t_philo in t_all, gives all p's an id, sets the
	fork pointers, and initializes the mutexes*/
void	alloc_phi_arr(t_all *all, int nb_phi)
{
	int	i;

	i = 0;
	all->phi_arr = ft_calloc(sizeof(t_philo), nb_phi + 1);
	while (i < nb_phi)
	{
		all->phi_arr[i].id = i + 1;
		all->phi_arr[i].last_ate = -1;
		all->phi_arr[i].all = all;
		i++;
	}
	set_fork_pointers(all->phi_arr, nb_phi);
	init_forks(all->phi_arr, nb_phi);
	all->dead = 0;
}

int		main(int ac, char **av)
{
	t_all	all;

	if (ac != 5 && ac != 6)
		write_error("Not enough arguments");
	all.nb_p = ft_atoi(av[1]);
	all.time_to_die = ft_atoi(av[2]);
	all.time_to_eat = ft_atoi(av[3]);
	all.time_to_sleep = ft_atoi(av[4]);
	all.times_each_must_eat = 0;
	all.sim_done = 0;
	if (av[5])
		all.times_each_must_eat = ft_atoi(av[5]);
	else
		all.times_each_must_eat = 100000;
	if (error_checks(&all) == 1)
		return (-1);
	alloc_phi_arr(&all, all.nb_p);
	if (create_threads(&all) == 1)
	{
		free_t_p(all.phi_arr, all.nb_p);
		return (1);
	}
	free_t_p(all.phi_arr, all.nb_p);
	return (0);
}
