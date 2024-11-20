/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_t_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:25:24 by tmilin            #+#    #+#             */
/*   Updated: 2024/11/10 21:26:25 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	after_taking_forks(t_philo *philo, t_params *params, long int c_time)
{
	long int	s_time;

	s_time = params->eat_time - params->sleep_time;
	if (philo->index % 2 != 0)
		after_taking_forks_impair(philo, params, c_time);
	else
	{
		philo->last_eat = get_current_time();
		usleep(params->eat_time * 1000);
		philo->count_eat += 1;
		for_eat(philo, params, c_time);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		for_sleep(philo, params, c_time);
		pthread_mutex_lock(&params->protect_dead);
		if (params->p_dead == 0 && params->eat_time + params->sleep_time
			+ s_time >= params->die_time)
			to_die_v2(philo, params, c_time);
		pthread_mutex_unlock(&params->protect_dead);
		usleep(params->sleep_time * 1000);
		for_think(philo, params, c_time);
	}
}

void	after_taking_forks_impair(t_philo *philo, t_params *params,
		long int c_time)
{
	long int	s_time;

	s_time = params->eat_time - params->sleep_time;
	philo->last_eat = get_current_time();
	usleep(params->eat_time * 1000);
	philo->count_eat += 1;
	for_eat(philo, params, c_time);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	for_sleep(philo, params, c_time);
	pthread_mutex_lock(&params->protect_dead);
	if (params->p_dead == 0 && params->eat_time + params->sleep_time
		+ s_time >= params->die_time)
		to_die_v2(philo, params, c_time);
	pthread_mutex_unlock(&params->protect_dead);
	usleep(params->sleep_time * 1000);
	for_think(philo, params, c_time);
}

void	for_eat(t_philo *philo, t_params *params, long int c_time)
{
	pthread_mutex_lock(&params->protect_dead);
	if (params->p_dead == 0)
		to_eat(philo, params, c_time);
	pthread_mutex_unlock(&params->protect_dead);
}

void	for_sleep(t_philo *philo, t_params *params, long int c_time)
{
	pthread_mutex_lock(&params->protect_dead);
	if (params->p_dead == 0)
		to_sleep(philo, params, c_time);
	pthread_mutex_unlock(&params->protect_dead);
}

void	for_think(t_philo *philo, t_params *params, long int c_time)
{
	pthread_mutex_lock(&params->protect_dead);
	if (params->p_dead == 0)
		to_think(philo, params, c_time);
	pthread_mutex_unlock(&params->protect_dead);
	if (params->eat_time > params->sleep_time)
		sleep_time(philo, params);
}
