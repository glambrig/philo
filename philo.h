/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:32:29 by glambrig          #+#    #+#             */
/*   Updated: 2023/12/15 15:25:40 by glambrig         ###   ########.fr       */
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
# include <errno.h>	//For global errno var, used to diagnose errors

typedef	struct	s_philo
{
	unsigned long long	id;
	short		is_eating;	//bool
	short		is_sleeping;	//bool
	short		is_thinking;	//bool
	short		died;	//bool
	short		lfork;	//1 if available, 0 if not
	short		rfork;	//1 if available, 0 if not
	short		has_lfork;	//1 if holding fork, 0 if not
	short		has_rfork;	//1 if holding fork, 0 if not
}	t_philo;

typedef struct	s_general
{
	unsigned int		num_of_phis;
	unsigned long long 	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	times_each_must_eat;
}	t_general;

/*Error and utility functions*/
void	write_error(char *s);
void	*ft_calloc(size_t nmemb, size_t size);
int	ft_atoi(char *s);

/*Init functions*/
void	init_t_general(int nb_philos, int time_to_die,int time_to_eat,
	int time_to_sleep, t_general **general);

#endif