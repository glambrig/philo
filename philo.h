/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <glambrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:32:29 by glambrig          #+#    #+#             */
/*   Updated: 2023/12/13 18:04:21 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef	struct	s_philo
{
	long long	id;
	int			fork_taken;	//bool
	short		is_eating;	//bool
	short		is_sleeping;	//bool
	short		is_thinking;	//bool
	short		died;	//bool
}	t_philo;

typedef struct	s_general
{
	int	num_of_phis;
	int time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_each_must_eat;
}	t_general;

void	write_error(char *s);

#endif