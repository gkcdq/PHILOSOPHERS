/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:30:09 by tmilin            #+#    #+#             */
/*   Updated: 2024/11/08 19:44:39 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_params
{
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	protect_printf;
	pthread_mutex_t	protect_dead;
	pthread_mutex_t	no_data_race;
	int				nbr_of_p;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				nbr_of_eat_time;
	int				p_dead;
	long int		start_time;
}					t_params;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		last_eat;
	int				index;
	int				count_eat;
	struct s_params	*params;
}					t_philo;

int					ft_atoi_philo(char *s, t_params *p);
void				check_min_max(long sign, long n, t_params *p);
long				get_current_time(void);
void				check_digit(char *s, t_params *p);
void				init_params(t_params **p, char **av);
int					init_philo(t_philo *philo, t_params *params);
void				*routine(void *arg);
void				eating_sleeping(t_philo *philo, t_params *params);
void				pair_forks(t_philo *philo, t_params *params,
						long int c_time);
void				impair_forks(t_philo *philo, t_params *params,
						long int c_time);
void				with_nbr_of_eat_time(t_philo *pl, t_params *pr);
void				whith_out_nbr_of_eat_time(t_philo *pl, t_params *pr);
void				check_death(t_philo *pl, t_params *pr, long int c_time);
void				sleep_time(t_philo *philo, t_params *params);
void				after_taking_forks_impair(t_philo *philo, t_params *params,
						long int c_time);
void				after_taking_forks(t_philo *philo, t_params *params,
						long int c_time);
void				to_eat(t_philo *philo, t_params *params, long int c_time);
void				to_sleep(t_philo *philo, t_params *params, long int c_time);
void				to_think(t_philo *philo, t_params *params, long int c_time);
void				free_for_philos(t_params *params, t_philo *philos);
void				eat_time_sup_die_time(t_philo *philo, t_params *params);
void				eating_sleeping_v2(t_philo *philo, t_params *params);
void				after_taking_forks_for_eat(t_philo *philo, t_params *params,
						long int c_time);
void				after_taking_forks_impair_kekw(t_philo *philo,
						t_params *params, long int c_time);
void				to_die(t_philo *philo, t_params *params, long int c_time,
						char c);
void				eating_sleeping_v3(t_philo *philo, t_params *params);
void				sleep_time_sup_die_time(t_philo *philo, t_params *params);
void				after_taking_forks_impair_sleep(t_philo *philo,
						t_params *params, long int c_time);
void				after_taking_forks_for_sleep(t_philo *philo,
						t_params *params, long int c_time);
void				to_die_v2(t_philo *philo, t_params *params,
						long int c_time);
void				for_think(t_philo *philo, t_params *params,
						long int c_time);
void				for_eat(t_philo *philo, t_params *params, long int c_time);
void				for_sleep(t_philo *philo, t_params *params,
						long int c_time);
void				i_m_done(t_philo *philo, t_params *params);
void				i_m_so_done_impair(t_philo *philo, t_params *params,
						long int c_time);

#endif
