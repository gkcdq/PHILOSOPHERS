#include "philo.h"

int	main(int ac, char **av)
{
	t_params *params;
	t_philo *philo;

	if (ac != 6)
	{
		printf("Usage: ./philo <nbr_of_p> <die_T> <eat_T> <sleep_T> <nbr_of_eat_T>\n");
		return (1);
	}
	init_params(params, av);
	init_philo(philo, params);
	return (0);
}