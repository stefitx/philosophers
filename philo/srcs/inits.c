/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:54:53 by atudor            #+#    #+#             */
/*   Updated: 2024/02/10 21:54:56 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_philo(t_global *global, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < global->nr_ph)
	{
		pthread_mutex_init(&philo[i].mtx_last_tm_eat, NULL);
		pthread_mutex_init(&philo[i].mtx_for_fullness, NULL);
		philo[i].id = i + 1;
		philo[i].times_eaten = 0;
		philo[i].i_am_full = 0;
		philo[i].last_time_eaten = ft_get_time(0);
		philo[i].global = global;
		pthread_mutex_init(&philo[i].right_fork, NULL);
		if (i > 0)
			philo[i].left_fork = &philo[i - 1].right_fork;
		i++;
	}
	philo[0].left_fork = &philo[global->nr_ph - 1].right_fork;
	global->philosophers = philo;
}

void	init_thread(t_global *global, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < global->nr_ph)
	{
		pthread_create(&philo[i].thread, NULL, &philo_routine, &philo[i]);
		i++;
	}
}

int	we_are_full(t_global *global)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < global->nr_ph)
	{
		pthread_mutex_lock(&global->philosophers[i].mtx_for_fullness);
		if (global->philosophers[i].i_am_full == 1)
			j++;
		pthread_mutex_unlock(&global->philosophers[i].mtx_for_fullness);
		i++;
	}
	if (j == i)
		return (1);
	else
		return (0);
}

void	check_death(t_philo	*philo)
{
	pthread_mutex_lock(&philo->global->mtx_global);
	pthread_mutex_unlock(&philo->global->mtx_global);
	pthread_mutex_lock(&philo->global->mtx_for_death);
	pthread_mutex_unlock(&philo->global->mtx_for_death);
}

int	check_meals(t_philo *philo)
{
	long	tm;

	if (philo->global->nr_must_eat != -1)
	{
		pthread_mutex_lock(&philo->mtx_for_fullness);
		if (philo->i_am_full != 1)
		{
			if (philo->times_eaten == philo->global->nr_must_eat)
			{
				philo->i_am_full = 1;
				tm = ft_get_time(philo->global->tm_begin);
				pthread_mutex_lock(&philo->global->mtx_print);
				printf(YELLOW "[%lu]" GREEN " %d is full\n", tm, philo->id);
				pthread_mutex_unlock(&philo->global->mtx_print);
				pthread_mutex_unlock(&philo->mtx_for_fullness);
				return (1);
			}
		}
	}
	pthread_mutex_unlock(&philo->mtx_for_fullness);
	return (0);
}
