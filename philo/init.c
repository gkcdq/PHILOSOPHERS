#include "philo.h"

void    init_params(t_params **p, char **av)
{
    int i;

    i = 0;
    (*p)->nbr_of_p = ft_atoi_philo(av[1], *p);
    (*p)->die_time = ft_atoi_philo(av[2], *p);
    (*p)->eat_time = ft_atoi_philo(av[3], *p);
    (*p)->sleep_time = ft_atoi_philo(av[4], *p);
    (*p)->nbr_of_eat_time = ft_atoi_philo(av[5], *p);
    pthread_mutex_init(&(*p)->mutex_dead, NULL);
    (*p)->forks = malloc(sizeof(pthread_mutex_t) * (*p)->nbr_of_p);
    while(i < (*p)->nbr_of_p)
    {
        pthread_mutex_init(&(*p)->forks[i], NULL);
        i++;
    }
    (*p)->p_dead = 0;
    pthread_mutex_init(&(*p)->protect_printf, NULL);
    (*p)->start_time = get_current_time();
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
        philo[i].count_eat = 0;
        pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
        i++;
    }
}