/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:19:19 by atudor            #+#    #+#             */
/*   Updated: 2024/02/28 20:19:21 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/philo_bonus.h"

long	ft_get_time(long time_start)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (printf("gettimeofday() FAILURE\n"));
	return (((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000)) - time_start);
}

void	print_str(t_philo *philo, char *str)
{
	long	tm;
	int		dead;

	sem_wait(philo->global->print);
	tm = ft_get_time(philo->global->tm_begin);
	printf(YELLOW "[%lu]" WHITE " %d %s\n", tm, philo->id, str);
	sem_post(philo->global->print);
}

void	ft_usleep(long long time, t_global *global, t_philo *philo)
{
	time += ft_get_time(0);
	while (ft_get_time(0) <= time)
	{
		check_death(global, philo);
		usleep(110);
	}
}
