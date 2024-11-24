/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_m_done.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:29:44 by tmilin            #+#    #+#             */
/*   Updated: 2024/11/24 18:29:45 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	i_m_so_done(t_philo *philo, t_params *params, long int c_time)
{
	if (philo->index % 2 != 0)
		i_m_so_done_impair(philo, params, c_time);
	else
	{
		philo->last_eat = get_current_time();
		philo->count_eat += 1;
		pthread_mutex_lock(&params->protect_dead);
		if (params->p_dead == 0)
			to_eat(philo, params, c_time);
		pthread_mutex_unlock(&params->protect_dead);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&params->no_data_race);
		usleep(params->eat_time * 1000);
		pthread_mutex_lock(&params->protect_dead);
		if (params->p_dead == 0)
		{
			to_sleep(philo, params, c_time);
			to_die(philo, params, c_time, 's');
		}
		pthread_mutex_unlock(&params->protect_dead);
	}
}

void	i_m_so_done_impair(t_philo *philo, t_params *params, long int c_time)
{
	philo->last_eat = get_current_time();
	philo->count_eat += 1;
	pthread_mutex_lock(&params->protect_dead);
	if (params->p_dead == 0)
		to_eat(philo, params, c_time);
	pthread_mutex_unlock(&params->protect_dead);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&params->no_data_race);
	usleep(params->eat_time * 1000);
	pthread_mutex_lock(&params->protect_dead);
	if (params->p_dead == 0)
	{
		to_sleep(philo, params, c_time);
		to_die(philo, params, c_time, 's');
	}
	pthread_mutex_unlock(&params->protect_dead);
}

void	eating_sleeping_v4(t_philo *philo, t_params *params)
{
	long int	c_time;

	c_time = get_current_time() - params->start_time;
	if (philo->index % 2 != 0)
		usleep(params->eat_time * 1000);
	if (philo->index % 2 == 0)
		pair_forks(philo, params, c_time);
	else
		impair_forks(philo, params, c_time);
	i_m_so_done(philo, params, c_time);
}

void	same_thing(t_philo *philo, t_params *params)
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
		pthread_mutex_unlock(&params->mutex_dead);
		pthread_mutex_unlock(&params->protect_dead);
		eating_sleeping_v4(philo, params);
	}
}

void	i_m_done(t_philo *philo, t_params *params)
{
	same_thing(philo, params);
}
