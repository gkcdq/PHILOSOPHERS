/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:44:24 by tmilin            #+#    #+#             */
/*   Updated: 2024/11/08 19:44:25 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_for_philos(t_params *params, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < params->nbr_of_p)
	{
		pthread_mutex_destroy(&params->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&params->protect_printf);
	pthread_mutex_destroy(&params->protect_dead);
	pthread_mutex_destroy(&params->mutex_dead);
	free(params->forks);
	free(philos);
	free(params);
}

int	main(int ac, char **av)
{
	t_params	*params;
	t_philo		*philos;
	int			i;

	if (ac < 5 || ac > 6)
	{
		printf("Usage: nbr_of_philo die_T eat_T sleep_T (nbr_of_eat_T)\n");
		return (1);
	}
	if (av[2][0] == '0')
		return 0;
	params = malloc(sizeof(t_params));
	init_params(&params, av);
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
