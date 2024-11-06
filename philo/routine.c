#include "philo.h"

void eating_sleeping(t_philo *philo, t_params *params)
{
    long int    current_time;

    current_time = get_current_time() - params->start_time;
    pthread_mutex_lock(&params->mutex_dead);
    if (get_current_time() - philo->last_eat >= params->die_time)
    {
        pthread_mutex_lock(&params->protect_printf);
        printf("[%ld] Le philosophe %d est mort\n", current_time, philo->index);
        pthread_mutex_unlock(&params->protect_printf);
        params->p_dead = 1;
        pthread_mutex_unlock(&params->mutex_dead);
        return;
    }
    pthread_mutex_unlock(&params->mutex_dead);
    if (philo->index % 2 != 0)
        usleep(params->eat_time * 1000);
    if (philo->index % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(&params->protect_printf);
        printf("[%ld] Le philosophe %d a pris la fourchette de droite\n", current_time, philo->index);
        pthread_mutex_unlock(&params->protect_printf);
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(&params->protect_printf);
        printf("[%ld] Le philosophe %d a pris la fourchette de gauche\n", current_time, philo->index);
        pthread_mutex_unlock(&params->protect_printf);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(&params->protect_printf);
        printf("[%ld] Le philosophe %d a pris la fourchette de gauche\n", current_time, philo->index);
        pthread_mutex_unlock(&params->protect_printf);
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(&params->protect_printf);
        printf("[%ld] Le philosophe %d a pris la fourchette de droite\n", current_time, philo->index);
        pthread_mutex_unlock(&params->protect_printf);
    }
    philo->last_eat = get_current_time();
	philo->count_eat += 1;
    pthread_mutex_lock(&params->protect_printf);
    printf("[%ld] Le philosophe %d est en train de Manger\n", current_time, philo->index);
    pthread_mutex_unlock(&params->protect_printf);
    usleep(params->eat_time * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_lock(&params->protect_printf);
    printf("[%ld] Le philosophe %d est en train de Penser\n", current_time, philo->index);
    pthread_mutex_unlock(&params->protect_printf);
    pthread_mutex_lock(&params->protect_printf);
    printf("[%ld] Le philosophe %d est en train de Dormir\n", current_time, philo->index);
    pthread_mutex_unlock(&params->protect_printf);
    usleep(params->sleep_time * 1000);
}

void *routine(void *arg)
{
    t_philo *philos;
    t_params *params; 
    
    philos = (t_philo *)arg;
    params = philos->params;
    while (philos->count_eat < params->nbr_of_eat_time)
    {
        pthread_mutex_lock(&params->mutex_dead);
        if (params->p_dead)
        {
            pthread_mutex_unlock(&params->mutex_dead);
            return (NULL);
        }
        pthread_mutex_unlock(&params->mutex_dead);
        eating_sleeping(philos, params);
    }
    return (NULL);
}
