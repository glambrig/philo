/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:09:22 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/22 16:18:01 by glambrig         ###   ########.fr       */
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

typedef struct timeval	t_timeval;
typedef struct s_all	t_all;

typedef struct s_philo
{
	unsigned short	id;
	long			last_ate;
	pthread_t		thr_id;	//init'd by pthread_create, used by pthread_join
	pthread_mutex_t	lfork;
	pthread_mutex_t	*rfork;
	short			has_lfork;
	short			has_rfork;
	struct s_all	*all;
}	t_philo;

struct	s_all
{
	int				nb_p;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				x_each_must_eat;
	short			sim_done;
	short			dead;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_status;
	pthread_mutex_t	m_all;
	pthread_mutex_t	m_unlock;
	t_philo			*phi_arr;
	t_timeval		start;
};

/*Utils*/
void		ft_putnbr(long long n);
void		ft_putstr(char *s);
void		*ft_calloc(size_t nmemb, size_t size);
long long	ft_atoi(char *s);
void		ft_putchar(char c);
/*Thread utils*/
void		p_status(long long timestamp, int p_nbr, char *action, t_philo *p);
int			rfork_is_null(t_philo *p, t_timeval start);
void		detach_t_unlock_m_all(t_philo *p);
int			check_death(t_philo *p, t_timeval start);

int			write_error(char *s);
int			error_checks(t_all *all);
void		free_t_p(t_philo *p, int nb_p);
long long	calc_elapsed_time(t_timeval start);
int			create_threads(t_all *all);
int			same_routine(t_philo *p, t_timeval start);
int			even_util(t_philo *p, t_timeval start, int i);
int			odd_util(t_philo *p, t_timeval start);

#endif