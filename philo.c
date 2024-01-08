/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:36:30 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/08 15:00:23 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*tf(void *arg)
// {
// 	t_philo *phi_arr = arg;
// 	if (phi_arr->id == 1)
// 	{
// 		pthread_mutex_lock(phi_arr->rfork);
// 		printf("locked by thread 1\n");
// 		sleep(5);
// 		pthread_mutex_unlock(phi_arr->rfork);
// 	}
// 	else if (phi_arr->id == 2)
// 	{
// 		pthread_mutex_lock(&(phi_arr->lfork));
// 		printf("locked by thread 2\n");
// 		sleep(5);
// 		pthread_mutex_unlock(&(phi_arr->lfork));		
// 	}
// 	return (NULL);
// }

// void	test(t_all *all)
// {
// 	pthread_create(&(all->phi_arr[0].thr_id), NULL, &tf, &(all->phi_arr[0]));
// 	pthread_create(&(all->phi_arr[1].thr_id), NULL, &tf, &(all->phi_arr[1]));
// 	pthread_join(all->phi_arr[0].thr_id, NULL);
// 	pthread_join(all->phi_arr[1].thr_id, NULL);
// }

/*Frees allocated memory and destroys mutexes (forks)*/
void	free_t_p(t_philo *p, int nb_p)
{
	int	i;

	i = 0;
	while (i < nb_p)
	{
		pthread_mutex_destroy(&(p[i].lfork));
		i++;
	}
	free(p);
}

void	set_fork_pointers(t_philo *phi_arr, int nb_phi)
{
	int	i;

	i = 0;
	while (i < nb_phi)
	{
		phi_arr[i].rfork = &phi_arr[i + 1].lfork;
		i++;
	}
	phi_arr[nb_phi].rfork = &phi_arr[0].lfork;
}

void	init_forks(t_philo *phi_arr, int nb_phi)
{
	int	i;

	i = 0;
	while (i < nb_phi)
	{
		pthread_mutex_init(&(phi_arr[i].lfork), NULL);
		i++;
	}
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
		all->phi_arr[i].all = all;
		i++;
	}
	set_fork_pointers(all->phi_arr, nb_phi);
	init_forks(all->phi_arr, nb_phi);
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
	error_checks(&all);
	if (av[5])
		all.times_each_must_eat = ft_atoi(av[5]);
	alloc_phi_arr(&all, all.nb_p);
	create_threads(&all);
	int i = 0;
	while (i < all.nb_p)
	{
		pthread_join(all.phi_arr[i].thr_id, NULL);
		i++;
	}
	free_t_p(all.phi_arr, all.nb_p);
}