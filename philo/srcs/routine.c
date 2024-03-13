/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:44:09 by atudor            #+#    #+#             */
/*   Updated: 2024/02/28 19:44:12 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	case_of_one(t_global *global, t_philo *philo)
{
	if (global->nr_ph == 1)
	{
		pthread_mutex_init(&philo[0].right_fork, NULL);
		philo[0].id = 1;
		global->philosophers = philo;
		philo[0].global = global;
		global->tm_begin = ft_get_time(0);
		pthread_create(&philo[0].thread, NULL, &philo_one, &philo[0]);
		pthread_join(philo[0].thread, NULL);
		free(philo);
		return (1);
	}
	return (0);
}

void	*philo_one(void *arg)
{
	t_philo	*philo;
	long	tm;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->right_fork);
	print_str(philo, "has taken right fork");
	ft_usleep(philo->global->die_time);
	tm = ft_get_time(philo->global->tm_begin);
	printf(RED "[%lu] %d %s\n", tm, philo->id, "has died");
	return (NULL);
}

void	living_well(t_philo	*philo)
{
	check_death(philo);
	pthread_mutex_lock(&philo->right_fork);
	print_str(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_str(philo, "has taken a fork");
	print_str(philo, "is eating");
	pthread_mutex_lock(&philo->mtx_last_tm_eat);
	philo->times_eaten++;
	philo->last_time_eaten = ft_get_time(philo->global->tm_begin);
	ft_usleep(philo->global->eat_time);
	pthread_mutex_unlock(&philo->mtx_last_tm_eat);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->global->mtx_global);
	pthread_mutex_unlock(&philo->global->mtx_global);
	if (philo->id % 2 == 0)
		ft_usleep(philo->global->eat_time / 10);
	while (1)
	{
		living_well(philo);
		if (check_meals(philo) == 1)
			return (NULL);
		check_death(philo);
		print_str(philo, "is sleeping");
		ft_usleep(philo->global->sleep_time);
		check_death(philo);
		print_str(philo, "is thinking");
	}
	return (NULL);
}
