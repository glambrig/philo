/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <glambrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:03:48 by glambrig          #+#    #+#             */
/*   Updated: 2023/12/13 19:47:24 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t mutex;//////////////AAAAAAAa

void	*func(void *n)
{
	(void)n;
	pthread_mutex_lock(&mutex);
	printf("bonjour\n");
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void	init_threads(pthread_t **threads, int nb_philos)
{
	int	i;

	i = 0;
	*threads = malloc(nb_philos * sizeof(pthread_t) + 1);
	while (i < nb_philos)
	{
		pthread_create(threads[i], NULL, &func, NULL);
		i++;
	}
}

void	init_t_general(int nb_philos, int time_to_die,
	int time_to_eat, int time_to_sleep, t_general *general)
{
	general = malloc(sizeof(t_general));
	if (!(general))
		write_error("Malloc failed\n");
	general->num_of_phis = nb_philos;
	general->time_to_die = time_to_die;
	general->time_to_eat = time_to_eat;
	general->time_to_sleep = time_to_sleep;
}

int	main(int ac, char **av)
{
	pthread_t	*philos;//trying to init a bunch of threads at once instead of always declaring more vars
	t_general	general;
	unsigned int			i;
	
	if (ac < 5 || atoi(av[1]) <= 0 || atoi(av[2]) <= 0 || atoi(av[3]) <= 0
		|| atoi(av[4]) <= 0)
		write_error("Argument error\n");
	init_t_general(atoi(av[1]), atoi(av[2]), atoi(av[3]),
		atoi(av[4]), &general);
	pthread_mutex_init(&mutex, NULL);
	init_threads(&philos, atoi(av[1]));//see above
	i = 0;
	while (i < general.num_of_phis)
		pthread_join(philos[i++], NULL);
	if (av[5] != NULL)
		general.times_each_must_eat = atoi(av[5]);
	pthread_mutex_destroy(&mutex);
}