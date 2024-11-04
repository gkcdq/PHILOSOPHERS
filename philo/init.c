#include "philo.h"

void    init_params(t_params **p, char **av)
{
    (*p)->nbr_of_p = ft_atoi_philo(av[1], *p);
    (*p)->die_time = ft_atoi_philo(av[2], *p);
    (*p)->eat_time = ft_atoi_philo(av[3], *p);
    (*p)->sleep_time = ft_atoi_philo(av[4], *p);
    (*p)->nbr_of_eat_time = ft_atoi_philo(av[5], *p);
    (*p)->forks = malloc(sizeof(pthread_mutex_t) * (*p)->nbr_of_p);
    (*p)->count_eat = 0;
    (*p)->p_dead = 0;
}

void    init_philo(t_philo *philo, t_params *params)
{
    int i;

    i = 0;
    while (i < params->nbr_of_p)
    {
        philo[i].index = i + 1;
        philo[i].last_eat = get_current_time();
        philo[i].left_fork = &params->forks[i];
        philo[i].right_fork = &params->forks[(i + 1) % params->nbr_of_p];
        philo[i].params = params;
        pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
        i++;
    }
}