/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:07:17 by tmilin            #+#    #+#             */
/*   Updated: 2024/11/01 18:12:28 by tmilin           ###   ########.fr       */
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
	if ((sign * n) > INT_MAX || (sign * n) < INT_MIN)
		free(p);
	return ;
}