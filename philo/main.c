#include "philo.h"

int	main(int ac, char **av)
{
	t_params *p;

	if (ac != 6)
		return (1);
	p->nbr_of_p = ft_atoi_philo(av[1], p);
	p->die_time = ft_atoi_philo(av[2], p);
	p->eat_time = ft_atoi_philo(av[3], p);
	p->sleep_time = ft_atoi_philo(av[4], p);
	p->nbr_of_eat_time = ft_atoi_philo(av[5], p);
    p->forks = malloc(sizeof(pthread_mutex_t) * p->nbr_of_p);
	return (0);
}