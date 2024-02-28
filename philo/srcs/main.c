/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:40:14 by atudor            #+#    #+#             */
/*   Updated: 2024/02/28 19:27:59 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	join_all(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->global->nr_ph)
	{
		pthread_detach(philo[i].thread);
		i++;
	}
}

void	rest_in_peace(t_global *global, long i)
{
	pthread_mutex_lock(&global->mtx_for_death);
	global->someone_died = 1;
	pthread_mutex_unlock(&global->mtx_for_death);
	pthread_mutex_lock(&global->mtx_global);
	pthread_mutex_lock(&global->mtx_print);
	printf("[%lu] %d %s\n", i, global->philosophers[i].id, "has died");
	pthread_mutex_unlock(&global->mtx_print);
}

void	god(t_global *global)
{
	int		i;
	long	last_time_eaten;
	long	current_time;

	while (1)
	{
		i = 0;
		while (i < global->nr_ph)
		{
			pthread_mutex_lock(&global->philosophers[i].mtx_last_tm_eat);
			last_time_eaten = global->philosophers[i].last_time_eaten;
			current_time = ft_get_time(global->tm_begin);
			pthread_mutex_unlock(&global->philosophers[i].mtx_last_tm_eat);
			if (current_time - last_time_eaten > global->die_time)
			{
				rest_in_peace(global, current_time);
				return ;
			}
			if (we_are_full(global) == 1)
				return ;
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_global	global;
	t_philo		*philo;

	if (!wrong_args(argc, argv, &global))
	{
		philo = malloc(sizeof(t_philo) * global.nr_ph);
		if (!philo)
			return (0);
		if (case_of_one(&global, philo) == 1)
			return (0);
		init_philo(&global, philo);
		init_thread(&global, philo);
		global.tm_begin = ft_get_time(0);
		pthread_mutex_unlock(&global.mtx_global);
		god(&global);
		join_all(philo);
		free(philo);
	}
	return (0);
}
