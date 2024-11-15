/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_t_forks_ip.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:25:33 by tmilin            #+#    #+#             */
/*   Updated: 2024/11/10 21:27:29 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_eat_impair(t_philo *philo, t_params *params, long int c_time)
{
	pthread_mutex_lock(&params->protect_printf);
	c_time = get_current_time() - params->start_time;
	printf("%ld %d is eating\n", c_time, philo->index);
	pthread_mutex_unlock(&params->protect_printf);
}

void	to_sleep_impair(t_philo *philo, t_params *params, long int c_time)
{
	pthread_mutex_lock(&params->protect_printf);
	c_time = get_current_time() - params->start_time;
	printf("%ld %d is sleeping\n", c_time, philo->index);
	pthread_mutex_unlock(&params->protect_printf);
}

void	to_think_impair(t_philo *philo, t_params *params, long int c_time)
{
	pthread_mutex_lock(&params->protect_printf);
	c_time = get_current_time() - params->start_time;
	printf("%ld %d is thinking\n", c_time, philo->index);
	pthread_mutex_unlock(&params->protect_printf);
}

void	after_taking_forks_impair(t_philo *philo, t_params *params,
		long int c_time)
{
	philo->last_eat = get_current_time();
	usleep(params->eat_time * 1000);
	philo->count_eat += 1;
	pthread_mutex_lock(&params->protect_dead);
	if (params->p_dead == 0)
		to_eat_impair(philo, params, c_time);
	pthread_mutex_unlock(&params->protect_dead);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(&params->protect_dead);
	if (params->p_dead == 0)
		to_sleep_impair(philo, params, c_time);
	pthread_mutex_unlock(&params->protect_dead);
	usleep(params->sleep_time * 1000);
	pthread_mutex_lock(&params->protect_dead);
	if (params->p_dead == 0)
		to_think_impair(philo, params, c_time);
	pthread_mutex_unlock(&params->protect_dead);
	if (params->eat_time > params->sleep_time)
		sleep_time(philo, params);
}
