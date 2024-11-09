/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:45:10 by tmilin            #+#    #+#             */
/*   Updated: 2024/11/08 19:45:11 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pair_forks(t_philo *philo, t_params *params, long int c_time)
{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&params->protect_printf);
		c_time = get_current_time() - params->start_time;
		if (params->p_dead == 0)
			printf("%ld %d has taken a fork\n", c_time, philo->index);
		pthread_mutex_unlock(&params->protect_printf);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&params->protect_printf);
		c_time = get_current_time() - params->start_time;
		if (params->p_dead == 0)
			printf("%ld %d has taken a fork\n", c_time, philo->index);
		pthread_mutex_unlock(&params->protect_printf);
}

void	impair_forks(t_philo *philo, t_params *params, long int c_time)
{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&params->protect_printf);
		c_time = get_current_time() - params->start_time;
		if (params->p_dead == 0)
			printf("%ld %d has taken a fork\n", c_time, philo->index);
		pthread_mutex_unlock(&params->protect_printf);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&params->protect_printf);
		c_time = get_current_time() - params->start_time;
		if (params->p_dead == 0)
			printf("%ld %d has taken a fork\n", c_time, philo->index);
		pthread_mutex_unlock(&params->protect_printf);
}

void	after_taking_forks_impair(t_philo *philo, t_params *params, long int c_time)
{
		philo->last_eat = get_current_time();
		philo->count_eat += 1;
		pthread_mutex_lock(&params->protect_printf);
		c_time = get_current_time() - params->start_time;
		if (params->p_dead == 0)
			printf("%ld %d is eating\n", c_time, philo->index);
		pthread_mutex_unlock(&params->protect_printf);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		usleep(params->eat_time * 1000);
		pthread_mutex_lock(&params->protect_printf);
		c_time = get_current_time() - params->start_time;
		if (params->p_dead == 0)
			printf("%ld %d is sleeping\n", c_time, philo->index);
		pthread_mutex_unlock(&params->protect_printf);
		usleep(params->sleep_time * 1000);
		pthread_mutex_lock(&params->protect_printf);
		c_time = get_current_time() - params->start_time;
		if (params->p_dead == 0)
			printf("%ld %d is thinking\n", c_time, philo->index);
		pthread_mutex_unlock(&params->protect_printf);

}

void	after_taking_forks(t_philo *philo, t_params *params, long int c_time)
{
		if (philo->index % 2 != 0)
			after_taking_forks_impair(philo, params, c_time);
		else
		{
			philo->last_eat = get_current_time();
			philo->count_eat += 1;
			pthread_mutex_lock(&params->protect_printf);
			c_time = get_current_time() - params->start_time;
			if (params->p_dead == 0)
				printf("%ld %d is eating\n", c_time, philo->index);
			pthread_mutex_unlock(&params->protect_printf);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			usleep(params->eat_time * 1000);
			pthread_mutex_lock(&params->protect_printf);
			c_time = get_current_time() - params->start_time;
			if (params->p_dead == 0)
				printf("%ld %d is sleeping\n", c_time, philo->index);
			pthread_mutex_unlock(&params->protect_printf);
			usleep(params->sleep_time * 1000);
			pthread_mutex_lock(&params->protect_printf);
			c_time = get_current_time() - params->start_time;
			if (params->p_dead == 0)
				printf("%ld %d is thinking\n", c_time, philo->index);
			pthread_mutex_unlock(&params->protect_printf);
		}
}

void	eating_sleeping(t_philo *philo, t_params *params)
{
	long int	c_time;

	c_time = get_current_time() - params->start_time;
	pthread_mutex_lock(&params->mutex_dead);
	if (get_current_time() - philo->last_eat >= params->die_time)
		check_death(philo, params, c_time);
	pthread_mutex_unlock(&params->mutex_dead);
	if (philo->index % 2 != 0)
		usleep(params->eat_time);
	if (philo->index % 2 == 0)
		pair_forks(philo, params, c_time);
	else
		impair_forks(philo, params, c_time);
	after_taking_forks(philo, params, c_time);
}

void	*routine(void *arg)
{
	t_philo		*philos;
	t_params	*params;
	long int	c_time;

	philos = (t_philo *)arg;
	params = philos->params;
	c_time = get_current_time() - params->start_time;
	if (params->nbr_of_p == 1)
	{
		printf("%ld %d has taken a fork\n", c_time, philos->index);
		usleep(params->die_time * 1000);
		c_time = get_current_time() - params->start_time;
		printf("%ld %d died\n", c_time, philos->index);
		return (NULL);
	}
	if (params->nbr_of_eat_time > 0)
	{
		with_nbr_of_eat_time(philos, params);
	}
	else if (params->nbr_of_eat_time == -1)
	{
		whith_out_nbr_of_eat_time(philos, params);
	}
	return (NULL);
}
