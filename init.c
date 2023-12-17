/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:27:04 by glambrig          #+#    #+#             */
/*   Updated: 2023/12/15 14:27:04 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_t_general(int nb_philos, int time_to_die,
	int time_to_eat, int time_to_sleep, t_general **general)
{
	*general = ft_calloc(sizeof(t_general), 1);
	if (!(*general))
		write_error("Malloc failed\n");
	(*general)->num_of_phis = nb_philos;
	(*general)->time_to_die = time_to_die;
	(*general)->time_to_eat = time_to_eat;
	(*general)->time_to_sleep = time_to_sleep;
}