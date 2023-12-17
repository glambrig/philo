/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:03:48 by glambrig          #+#    #+#             */
/*   Updated: 2023/12/17 11:57:07 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t mutex;//////////////AAAAAAAa

void	*func(void *n)
{
	int i = 0;
	(void)n;
	while (i < 5)
	{
		pthread_mutex_lock(&mutex);
		printf("bonjour\n");
		i++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void	init_threads(pthread_t **threads, int nb_philos)
{
	int	i;

	*threads = ft_calloc(sizeof(pthread_t), (nb_philos + 1));
	if (!(*threads))
		write_error("Malloc failed\n");
	i = 0;
	while (i < nb_philos)
	{
		if (pthread_create(*threads + i, NULL, &func, NULL) != 0)
			write_error("pthread_create failed\n");
		i++;
	}
}

void	join_threads(pthread_t **threads, int nb_philos)
{
	int	i;

	i = 0;
	while (i < nb_philos)
	{
		if (pthread_join(*(*threads + i), NULL) != 0)
			write_error("pthread_join failed\n");
		i++;
	}
}

int	main(int ac, char **av)
{
	pthread_t	*philos;
	t_general	*general;
	
	/*Errors*/
	if (ac < 5 || atoi(av[1]) <= 0 || atoi(av[2]) <= 0 || atoi(av[3]) <= 0
		|| atoi(av[4]) <= 0)
		write_error("Argument error\n");

	/*Init*/
	init_t_general(atoi(av[1]), atoi(av[2]), atoi(av[3]),
		atoi(av[4]), &general);
	if (av[5] != NULL)
		general->times_each_must_eat = atoi(av[5]);
	pthread_mutex_init(&mutex, NULL);
	init_threads(&philos, general->num_of_phis);
	join_threads(&philos, general->num_of_phis);

	/*Free*/
	pthread_mutex_destroy(&mutex);
	free(philos);
	free(general);
}
