#include "philo.h"

void	eating_sleeping(t_philo *philo, t_params *params)
{
    int max;

    max = params->nbr_of_p;
    if (get_current_time() - philo->last_eat >= params->die_time)
    {
        printf("Le philosophe %d est mort", philo->index);
        params->p_dead = 1;
        return ;
    }
	pthread_mutex_lock(philo->left_fork);
	printf("Le philosophe %d a pris sa fourchette\n", philo->index);
	pthread_mutex_lock(philo->right_fork);
	printf("Le philosophe %d a pris la fourchette de droite\n", philo->index);
	philo->last_eat = get_current_time();
    if (philo->index == max)
        params->count_eat += 1;
	printf("Le philosophe %d est entrain de Manger\n", philo->index);
	usleep(params->eat_time * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	printf("Le philosophe %d est entrain de Penser\n", philo->index);
	printf("Le philosophe %d est entrain de Dormir\n", philo->index);
	usleep(params->sleep_time * 1000);
	return ;
}

void	*routine(void *arg)
{
	t_philo *philo;
	t_params *params;

	philo = (t_philo *)arg;
	params = philo->params;
	while (params->p_dead == 0 && (params->count_eat < params->nbr_of_eat_time))
	{
		eating_sleeping(philo, params);
	}
    return ;
}