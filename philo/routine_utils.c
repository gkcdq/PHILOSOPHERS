/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:45:26 by tmilin            #+#    #+#             */
/*   Updated: 2024/11/08 19:45:37 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	with_nbr_of_eat_time(t_philo *philos, t_params *params)
{
	if (params->eat_time >= params->die_time)
		eat_time_sup_die_time(philos, params);
	else if (params->sleep_time >= params->die_time)
		sleep_time_sup_die_time(philos, params);
	else if (params->eat_time + params->sleep_time >= params->die_time)
		sleep_time_sup_die_time(philos, params);
	else
	{
		while (philos->count_eat < params->nbr_of_eat_time)
		{
			pthread_mutex_lock(&params->mutex_dead);
			pthread_mutex_lock(&params->protect_dead);
			if (params->p_dead)
			{
				pthread_mutex_unlock(&params->mutex_dead);
				pthread_mutex_unlock(&params->protect_dead);
				return ;
			}
			pthread_mutex_unlock(&params->protect_dead);
			pthread_mutex_unlock(&params->mutex_dead);
			eating_sleeping(philos, params);
		}
	}
}

void	whith_out_nbr_of_eat_time(t_philo *philos, t_params *params)
{
	if (params->eat_time >= params->die_time)
		eat_time_sup_die_time(philos, params);
	else if (params->sleep_time >= params->die_time)
		sleep_time_sup_die_time(philos, params);
	else if (params->eat_time + params->sleep_time >= params->die_time)
		sleep_time_sup_die_time(philos, params);
	else
	{
		while (1)
		{
			pthread_mutex_lock(&params->mutex_dead);
			pthread_mutex_lock(&params->protect_dead);
			if (params->p_dead)
			{
				pthread_mutex_unlock(&params->mutex_dead);
				pthread_mutex_unlock(&params->protect_dead);
				return ;
			}
			pthread_mutex_unlock(&params->protect_dead);
			pthread_mutex_unlock(&params->mutex_dead);
			eating_sleeping(philos, params);
		}
	}
}

void	check_death(t_philo *philo, t_params *params, long int c_time)
{
	pthread_mutex_lock(&params->protect_printf);
	c_time = get_current_time() - params->start_time;
	printf("%ld %d died\n", c_time, philo->index);
	pthread_mutex_unlock(&params->protect_printf);
	params->p_dead = 1;
	return ;
}

void	sleep_time(t_philo *philo, t_params *params)
{
	int	s_time;

	(void)philo;
	s_time = params->eat_time - params->sleep_time;
	usleep(s_time * 1000);
}
