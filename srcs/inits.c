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
		philo[i].id = i + 1;
		philo[i].times_eaten = 0;
		philo[i].i_am_full = 0;
		philo[i].last_time_eaten = ft_get_time(0);
		philo[i].global = global;
		philo[i].global->someone_died = 0;
		pthread_mutex_init(&philo[i].right_fork, NULL);
		pthread_mutex_init(&philo[i].mtx_for_god, NULL);
		if (i > 0)
			philo[i].left_fork = &philo[i - 1].right_fork;
		i++;
	}
	philo[0].left_fork = &philo[global->nr_ph - 1].right_fork;
}

void	init_thread(t_global *global, t_philo *philo)
{
	int i;
	i = 0;
	while (i < global->nr_ph)
	{
		pthread_create(&philo[i].thread, NULL, &philo_routine, &philo[i]);
		i++;
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->mtx_for_god);
	if (philo->global->someone_died == 1)
	{
		pthread_mutex_unlock(&philo->mtx_for_god);
		return NULL;
	}
	pthread_mutex_unlock(&philo->mtx_for_god);
	pthread_mutex_lock(&philo->global->mtx_global);
	pthread_mutex_unlock(&philo->global->mtx_global);
	if (philo->id % 2 == 0)
		ft_usleep(philo->global->eat_time/10);
	while (1)
	{
		pthread_mutex_lock(&philo->right_fork);
			print_str(*philo, "has taken right fork");
		pthread_mutex_lock(philo->left_fork);
		print_str(*philo, "has taken left fork");
		usleep(philo->global->sleep_time * 1000);
		print_str(*philo, "is eating");
		pthread_mutex_lock(&philo->mtx_for_god);
		philo->times_eaten += 1;
		usleep(philo->global->eat_time * 1000);
		philo->last_time_eaten = ft_get_time(philo->global->tm_begin);
		pthread_mutex_unlock(&philo->mtx_for_god);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		print_str(*philo, "is sleeping");
		usleep(philo->global->sleep_time * 1000);
		print_str(*philo, "is thinking");
	}
	return NULL;
}

void	god(t_philo *philo, t_global *global)
{
	int	i;
	long	last_time_eaten;

	while (!global->someone_died)
	{
		i = 0;
		while (i < global->nr_ph)
		{
			pthread_mutex_lock(&philo[i].mtx_for_god);
			last_time_eaten = philo[i].last_time_eaten;
			pthread_mutex_unlock(&philo[i].mtx_for_god);
			if (ft_get_time(global->tm_begin) - last_time_eaten > philo->global->die_time)
			{
				pthread_mutex_lock(&global->mtx_global);
				philo[i].global->someone_died = 1;
				print_str(philo[i], "has died");
				pthread_mutex_unlock(&global->mtx_global);
				return ;
			}
			i++;
		}
		if (global->someone_died == 1)
			return ;
	}
}
