/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:19:07 by atudor            #+#    #+#             */
/*   Updated: 2024/02/28 20:19:09 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/philo_bonus.h"

void	init_philo(t_global *global, t_philo *philo)
{
	int	i;

	global->philosophers = philo;
	i = 0;
	while (i < global->nr_ph)
	{
		philo[i].id = i + 1;
		philo[i].times_eaten = 0;
		philo[i].i_am_full = 0;
		philo[i].last_time_eaten = ft_get_time(0);
		philo[i].global = global;
		i++;
	}
}

void	init_process(t_global *global, t_philo *philo, sem_t *forks)
{
	int	i;

	i = 0;
	while (i < global->nr_ph)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			philo_routine(global, &philo[i], forks);
			exit(0);
		}
		i++;
	}
}

int	case_of_one(t_global *global, t_philo *philo)
{
	if (global->nr_ph == 1)
	{
		philo[0].id = 1;
		global->philosophers = philo;
		philo[0].global = global;
		global->tm_begin = ft_get_time(0);
		philo[0].pid = fork();
		if (philo[0].pid == 0)
		{
			sem_wait(global->forks);
			print_str(&philo[0], "has taken a fork");
			ft_usleep(global->die_time + 10, global, philo);
			exit(0);
		}
		return 1;
	}
	return 0;
}