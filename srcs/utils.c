/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leftovers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 23:54:58 by atudor            #+#    #+#             */
/*   Updated: 2024/02/10 23:55:05 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	ft_get_time(long time_start)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (printf("gettimeofday() FAILURE\n"));
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000) - time_start);
}

void	print_str(t_philo *philo, char *str)
{
	long	tm;

	pthread_mutex_lock(&philo->global->mtx_for_death);
	if (philo->global->someone_died != 1)
	{
		pthread_mutex_lock(&philo->global->mtx_print);
		tm = ft_get_time(philo->global->tm_begin);
		printf("[%lu] %d %s\n",tm, philo->id, str);
		pthread_mutex_unlock(&philo->global->mtx_print);
	}
	if (philo->global->someone_died == 1)
	{
		pthread_mutex_lock(&philo->global->mtx_print);
		tm = ft_get_time(philo->global->tm_begin);
		printf("[%lu] %d %s\n",tm, philo->id, str);
		pthread_mutex_unlock(&philo->global->mtx_print);
	}
	pthread_mutex_unlock(&philo->global->mtx_for_death);
}

void	ft_usleep(long long time)
{
	time += ft_get_time(0);
	while (ft_get_time(0) <= time)
		usleep(200);
}

