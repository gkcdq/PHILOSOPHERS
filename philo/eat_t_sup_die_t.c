#include "philo.h"

void	eat_time_sup_die_time(t_philo *philo, t_params *params)
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
		eating_sleeping_v2(philo, params);
	}
}
void	eating_sleeping_v2(t_philo *philo, t_params *params)
{
	long int	c_time;

	c_time = get_current_time() - params->start_time;
	if (philo->index % 2 != 0)
		usleep(params->eat_time);
	if (philo->index % 2 == 0)
		pair_forks(philo, params, c_time);
	else
		impair_forks(philo, params, c_time);
	after_taking_forks_for_eat(philo, params, c_time);
}
void	after_taking_forks_for_eat(t_philo *philo, t_params *params,
		long int c_time)
{
	if (philo->index % 2 != 0)
		after_taking_forks_impair_kekw(philo, params, c_time);
	else
	{
		pthread_mutex_lock(&params->protect_dead);
		if (params->p_dead == 0)
			to_die(philo, params, c_time);
		pthread_mutex_unlock(&params->protect_dead);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
}

void	after_taking_forks_impair_kekw(t_philo *philo, t_params *params,
		long int c_time)
{
	pthread_mutex_lock(&params->protect_dead);
	if (params->p_dead == 0)
		to_die(philo, params, c_time);
	pthread_mutex_unlock(&params->protect_dead);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return ;
}

void	to_die(t_philo *philo, t_params *params, long int c_time)
{
	usleep(params->die_time * 1000);
	pthread_mutex_lock(&params->protect_printf);
	c_time = get_current_time() - params->start_time;
	printf("%ld %d is dead\n", c_time, philo->index);
	pthread_mutex_unlock(&params->protect_printf);
	params->p_dead = 1;
}