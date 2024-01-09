/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:09:22 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/08 13:44:50 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct	timeval	t_timeval;
struct	s_all;

typedef struct	s_philo
{
	unsigned short	id;
	pthread_t		thr_id;	//init'd by pthread_create, used by pthread_join
	pthread_mutex_t	lfork;
	pthread_mutex_t	*rfork;
	short			dead;	//if p is dead, dead == 1 else 0
	struct s_all	*all;
}	t_philo;

typedef struct	s_all
{
	int			nb_p;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	int			times_each_must_eat;
	t_philo		*phi_arr;
	t_timeval	start;	//start value of timer
}	t_all;

void		ft_putnbr(long long n);
void		ft_putstr(char *s);
void		*ft_calloc(size_t nmemb, size_t size);
long long	ft_atoi(char *s);
void		write_error(char *s);
void		error_checks(t_all *all);
void		free_t_p(t_philo *p, int nb_p);
void		p_status(int timestamp, int p_nbr, char *action);
t_timeval	calc_elapsed_time(t_timeval start);
void		create_threads(t_all *all);

#endif