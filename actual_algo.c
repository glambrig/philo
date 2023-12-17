/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actual_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <glambrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:08:58 by glambrig          #+#    #+#             */
/*   Updated: 2023/12/17 19:34:24 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*even_num(void *general)
// {
// 	int i = 0;
// 	while (i < 1)
// 	{
// 		pthread_mutex_lock(&((t_general *)general)->mutex);
// 		printf("even\n");
// 		i++;
// 		pthread_mutex_unlock(&((t_general *)general)->mutex);
// 	}
// 	return NULL;
// }

// void	*odd_num(void *general)
// {
// 	int i = 0;
// 	while (i < 1)
// 	{
// 		pthread_mutex_lock(&((t_general *)general)->mutex);
// 		printf("odd\n");
// 		i++;
// 		pthread_mutex_unlock(&((t_general *)general)->mutex);
// 	}
// 	return NULL;
// }

void	*odd_num(void *general)
{
	//starting with philo 1 (p1), check if both forks are available
		//if so, take them and eat
		//otherwise, wait. (won't happen with p1 on first go, this cond is mainly for others p-s)
	//do this for all odd numbered p-s until forks are unavailable
	//p-s that have forks eat, and put their forks back down
	//once this happens, p2 and all even p-s that can take forks and eat
	//repeat, starting at p3.
		/*
		 this means that the last one that couldn't previously eat (in the case of pN=5, this would be p5
		 	because p1 and p3 take forks, but p5 can't bc p1 took his right fork) will eat after two ticks.
		*/
}