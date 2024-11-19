/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:44:16 by tmilin            #+#    #+#             */
/*   Updated: 2024/11/08 19:48:39 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_params(t_params **p, char **av)
{
	int	i;

	i = 0;
	(*p)->nbr_of_p = ft_atoi_philo(av[1], *p);
	(*p)->die_time = ft_atoi_philo(av[2], *p);
	(*p)->eat_time = ft_atoi_philo(av[3], *p);
	(*p)->sleep_time = ft_atoi_philo(av[4], *p);
	if (av[5])
		(*p)->nbr_of_eat_time = ft_atoi_philo(av[5], *p);
	else
		(*p)->nbr_of_eat_time = -1;
	pthread_mutex_init(&(*p)->mutex_dead, NULL);
	(*p)->forks = malloc(sizeof(pthread_mutex_t) * (*p)->nbr_of_p);
	while (i < (*p)->nbr_of_p)
	{
		pthread_mutex_init(&(*p)->forks[i], NULL);
		i++;
	}
	(*p)->p_dead = 0;
	pthread_mutex_init(&(*p)->protect_printf, NULL);
	(*p)->start_time = get_current_time();
	pthread_mutex_init(&(*p)->protect_dead, NULL);
	pthread_mutex_init(&(*p)->p_t_d_r, NULL);
}

void	init_philo(t_philo *philo, t_params *params)
{
	int	i;
	int	res;

	i = 0;
	while (i < params->nbr_of_p)
	{
		philo[i].index = i + 1;
		philo[i].last_eat = get_current_time();
		philo[i].left_fork = &params->forks[i];
		philo[i].right_fork = &params->forks[(i + 1) % params->nbr_of_p];
		philo[i].params = params;
		philo[i].count_eat = 0;
		res = pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		if(res != 0)
		{
			printf("Error : thread creation");
			return ;
		}
		i++;
	}
}
