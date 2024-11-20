/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_die.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:03:07 by tmilin            #+#    #+#             */
/*   Updated: 2024/11/20 14:03:08 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_eat(t_philo *philo, t_params *params, long int c_time)
{
	pthread_mutex_lock(&params->protect_printf);
	c_time = get_current_time() - params->start_time;
	printf("%ld %d is eating\n", c_time, philo->index);
	pthread_mutex_unlock(&params->protect_printf);
}

void	to_sleep(t_philo *philo, t_params *params, long int c_time)
{
	pthread_mutex_lock(&params->protect_printf);
	c_time = get_current_time() - params->start_time;
	printf("%ld %d is sleeping\n", c_time, philo->index);
	pthread_mutex_unlock(&params->protect_printf);
}

void	to_think(t_philo *philo, t_params *params, long int c_time)
{
	pthread_mutex_lock(&params->protect_printf);
	c_time = get_current_time() - params->start_time;
	printf("%ld %d is thinking\n", c_time, philo->index);
	pthread_mutex_unlock(&params->protect_printf);
}

void	to_die(t_philo *philo, t_params *params, long int c_time, char c)
{
	if (c == 'e')
	{
		usleep(params->die_time * 1000);
		pthread_mutex_lock(&params->protect_printf);
		c_time = get_current_time() - params->start_time;
		printf("%ld %d is dead\n", c_time, philo->index);
		pthread_mutex_unlock(&params->protect_printf);
		params->p_dead = 1;
	}
	if (c == 's')
	{
		usleep((params->die_time - params->eat_time) * 1000);
		pthread_mutex_lock(&params->protect_printf);
		c_time = get_current_time() - params->start_time;
		printf("%ld %d is dead\n", c_time, philo->index);
		pthread_mutex_unlock(&params->protect_printf);
		params->p_dead = 1;
	}
}

void	to_die_v2(t_philo *philo, t_params *params, long int c_time)
{
	long int	p_time;
	long int	s_time;

	s_time = params->eat_time - params->sleep_time;
	p_time = params->eat_time + params->sleep_time - params->die_time;
	if (p_time < 0)
		p_time = -p_time;
	usleep((s_time + p_time) * 1000);
	pthread_mutex_lock(&params->protect_printf);
	c_time = get_current_time() - params->start_time;
	printf("%ld %d is dead\n", c_time, philo->index);
	pthread_mutex_unlock(&params->protect_printf);
	params->p_dead = 1;
}
