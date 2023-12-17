/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <glambrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:03:48 by glambrig          #+#    #+#             */
/*   Updated: 2023/12/17 18:23:50 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*test_func(void *general)
// {
// 	int i = 0;
// 	while (i < 500)
// 	{
// 		pthread_mutex_lock(&((t_general *)general)->mutex);
// 		printf("bonjour\n");
// 		i++;
// 		pthread_mutex_unlock(&((t_general *)general)->mutex);
// 	}
// 	return NULL;
// }

void	init_threads(pthread_t **threads, int nb_philos, t_general *general)
{
	int	i;

	*threads = ft_calloc(sizeof(pthread_t), (nb_philos + 1));
	if (!(*threads))
		write_error("Malloc failed\n");
	i = 0;
	while (i < nb_philos)
	{
		if (nb_philos % 2 == 0)
		{
			if (pthread_create(*threads + i, NULL, &even_num, general) != 0)
				write_error("pthread_create failed\n");
		}
		else if (nb_philos % 2 == 1)
		{
			if (pthread_create(*threads + i, NULL, &odd_num, general) != 0)
				write_error("pthread_create failed\n");			
		}
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
	t_general	*general;
	pthread_t	*threads;
	
	/*Errors*/
	if (ac < 5 || atoi(av[1]) <= 0 || atoi(av[2]) <= 0 || atoi(av[3]) <= 0
		|| atoi(av[4]) <= 0)
		write_error("Argument error\n");

	/*Init*/
	init_t_general(atoi(av[1]), atoi(av[2]), atoi(av[3]),
		atoi(av[4]), &general);
	if (av[5] != NULL)
		general->times_each_must_eat = atoi(av[5]);
	pthread_mutex_init(&general->mutex, NULL);
	init_threads(&threads, general->num_of_phis, general);
	join_threads(&threads, general->num_of_phis);

	/*Algorithm*/

	/*Free*/
	pthread_mutex_destroy(&general->mutex);
	free(general->philo);
	free(general);
	free(threads);
}
