/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:07:17 by tmilin            #+#    #+#             */
/*   Updated: 2024/11/08 19:48:18 by tmilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_atoi_philo(char *s, t_params *p)
{
	int		i;
	long	sign;
	long	n;

	i = 0;
	n = 0;
	sign = 1;
	check_digit(s, p);
	while (s[i] <= 32)
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + (s[i] - '0');
		i++;
	}
	check_min_max(sign, n, p);
	return ((int)sign * (int)n);
}

void	check_min_max(long sign, long n, t_params *p)
{
	if ((sign * n) > INT_MAX || (sign * n) < 0)
	{
		printf("Error : Invalid value\n");
		free(p);
		exit(0);
	}
	return ;
}

void	check_digit(char *s, t_params *p)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '-' || s[i] == '+')
			i++;
		if ((s[i] < '0' || s[i] > '9'))
		{
			printf("Error : Invalid digit\n");
			free(p);
			exit(0);
		}
		i++;
	}
}

void	action_sleep(t_philo *philo, t_params *params, long int c_time)
{
	usleep(params->die_time * 1000);
	pthread_mutex_lock(&params->protect_dead);
	params->p_dead = 1;
	pthread_mutex_unlock(&params->protect_dead);
	pthread_mutex_lock(&params->protect_printf);
	printf("%ld %d died\n", c_time, philo->index);
	return ;



}

