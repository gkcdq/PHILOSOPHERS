/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:30:09 by tmilin            #+#    #+#             */
/*   Updated: 2024/11/01 18:08:11 by tmilin           ###   ########.fr       */
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
	pthread_mutex_t	*forks;
}					t_params;

typedef struct s_philosopher
{
	int				id;
	int				nbr_of_eat;
	pthread_t		thread;
	struct s_params	*params;
}					t_philo;

// utils.c
int					ft_atoi_philo(char *s, t_params *p);
void				check_min_max(long sign, long n, t_params *p);

#endif
