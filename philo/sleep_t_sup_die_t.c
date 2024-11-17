/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_t_sup_die_t.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:53:52 by tmilin            #+#    #+#             */
/*   Updated: 2024/11/17 13:53:54 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_time_sup_die_time(t_philo *philo, t_params *params)
{
	while (1)
	{
		pthread_mutex_lock(&params->mutex_dead);
		if (params->p_dead)
		{
			pthread_mutex_unlock(&params->mutex_dead);
			return ;
		}
		pthread_mutex_unlock(&params->mutex_dead);
		eating_sleeping_v3(philo, params);
	}
}

void	eating_sleeping_v3(t_philo *philo, t_params *params)
{
	long int	c_time;

	c_time = get_current_time() - params->start_time;
	if (philo->index % 2 != 0)
		usleep(params->eat_time);
	if (philo->index % 2 == 0)
		pair_forks(philo, params, c_time);
	else
		impair_forks(philo, params, c_time);
	after_taking_forks_for_sleep(philo, params, c_time);
}

void	after_taking_forks_for_sleep(t_philo *philo, t_params *params,
		long int c_time)
{
	if (philo->index % 2 != 0)
		after_taking_forks_impair_sleep(philo, params, c_time);
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
		pthread_mutex_lock(&params->protect_dead);
		if (params->p_dead == 0)
			to_die(philo, params, c_time);
		pthread_mutex_unlock(&params->protect_dead);
	}
}

void	after_taking_forks_impair_sleep(t_philo *philo, t_params *params,
		long int c_time)
{
	philo->last_eat = get_current_time();
	philo->count_eat += 1;
	pthread_mutex_lock(&params->protect_dead);
	if (params->p_dead == 0)
		to_eat(philo, params, c_time);
	pthread_mutex_unlock(&params->protect_dead);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(&params->protect_dead);
	if (params->p_dead == 0)
		to_die(philo, params, c_time);
	pthread_mutex_unlock(&params->protect_dead);
}
