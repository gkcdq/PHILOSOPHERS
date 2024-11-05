#include "philo.h"

void    free_for_philos(t_params *params, t_philo *philos)
{
    int i;

    i = 0;
	while (i < params->nbr_of_p)
    {
        pthread_mutex_destroy(&params->forks[i]);
		i++;
    }
	free(params->forks);
    free(philos);
    free(params);
}

int main(int argc, char **argv)
{
	t_params *params;
	t_philo *philos;
	int	i;

    if (argc < 6)
    {
        printf("Usage: nbr_of_philos die_time eat_time sleep_time nbr_of_eat_time\n");
        return (1);
    }
    params = malloc(sizeof(t_params));
    init_params(&params, argv);
    philos = malloc(sizeof(t_philo) * params->nbr_of_p);
    init_philo(philos, params);
	i = 0;
	while (i < params->nbr_of_p)
    {
        pthread_join(philos[i].thread, NULL);
		i++;
    }
    free_for_philos(params, philos);
    return (0);
}
