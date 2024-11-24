#include "philo.h"

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
		eating_sleeping_v3(philo, params);
	}
}

void	i_m_done(t_philo *philo, t_params *params)
{
	same_thing(philo, params);
}