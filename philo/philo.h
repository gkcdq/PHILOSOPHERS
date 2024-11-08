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
	int				nbr_of_p;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				nbr_of_eat_time;
	int				p_dead;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	protect_printf;
	long int		start_time;
}					t_params;

typedef struct s_philo
{
	int				index;
	int				count_eat;
	long			last_eat;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_params	*params;
}					t_philo;

// utils.c
int					ft_atoi_philo(char *s, t_params *p);
void				check_min_max(long sign, long n, t_params *p);
long				get_current_time(void);

// init.c
void				init_params(t_params **p, char **av);
void				init_philo(t_philo *philo, t_params *params);

// routine.c
void				*routine(void *arg);
void				eating_sleeping(t_philo *philo, t_params *params);

// routine_utils.c
void				with_nbr_of_eat_time(t_philo *pl, t_params *pr);
void				whith_out_nbr_of_eat_time(t_philo *pl, t_params *pr);
void				check_death(t_philo *pl, t_params *pr, long int c_time);

// main.c
void				free_for_philos(t_params *params, t_philo *philos);

#endif
